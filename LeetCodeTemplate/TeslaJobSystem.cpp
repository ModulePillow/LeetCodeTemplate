// WARNING:
// This C++ unit was built by Pillow and
// will be provided to Codility for the audition.

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <chrono>
#include <immintrin.h>
#include <string_view>
#include <optional>
#include <algorithm>

// 1. Mutexes
// std::mutex std::timed_mutex std::recursive_mutex
//
// 2. Lock Mgrs
// std::lock_guard std::scoped_lock std::unique_lock std::shared_lock
// std::lock(...)
// 
// 3. Atomics
// std::atomic<T> load, store, fetch_add, fetch_sub
//
// 4. CV
// std::condition_variable (with std::unique_ptr)
// wait(lock, []{ return ready; }), notify_one, notify_all

namespace TeslaMT
{
   int32_t WorkerThreadCount = 4; // Can change it when start the application
   constexpr int32_t CacheLineSize = 64;
   constexpr uint32_t ArraySize = 32;

   using Job = std::function<void()>;
   using Action = Job;
   using Worker = void (*)(const std::atomic<bool>& stop_token, const int32_t threadIdx);

   struct GenConditionVar
   {
      std::mutex mute;
      std::condition_variable cvar;
      uint64_t generation = 0;

      void Wait(uint64_t old_gen)
      {
         std::unique_lock lock(mute);
         // Wait until the generation num is changed.
         cvar.wait(lock, [this, old_gen] { return generation != old_gen; });
      }

      void Notify()
      {
         {
            std::lock_guard<std::mutex> lock(mute);
            generation++;
         }
         cvar.notify_all();
      }
   };

   // Simulate Barrier in C++ 20.
   class Barrier
   {
   private:
      const int32_t WorkerCount;
      const Action Completion;

      std::mutex mute;
      GenConditionVar barrierCV;
      int32_t count = 0;
      uint64_t currentGeneration = 0;

   public:
      Barrier(int32_t workerCount, Action completion) :
         WorkerCount(workerCount),
         Completion(completion)
      {
         count = workerCount;
      }

      void ArriveAndWait()
      {
         std::unique_lock lock(mute);

         if (count < 1) return;

         uint64_t currentGen = currentGeneration;

         count--;
         if (count == 0) // The last guest.
         {
            if (Completion) Completion();
            count = WorkerCount;
            currentGeneration++;

            lock.unlock();
            barrierCV.Notify();
         }
         else
         {
            lock.unlock(); // Unlock it earlier.
            barrierCV.Wait(currentGen);
         }
      }
   };

   inline void Yield()
   {
      std::this_thread::yield();
   }

   inline void SpinLoopHint()
   {
#if defined(_MSC_VER) && defined(_M_X64)
      _mm_pause();
#elif defined(__clang__) && (defined(__aarch64__) || defined(__arm__))
      __builtin_arm_yield();
#else
      // Fake spin; it's NOT a spin.
      Yield();
#endif
   }

   inline void RequestStop(std::atomic<bool>& stop_token)
   {
      stop_token.store(true, std::memory_order_release);
   }

   inline bool IsStopped(const std::atomic<bool>& stop_token)
   {
      return stop_token.load(std::memory_order_acquire);
   }
}

namespace TeslaMT::JobSystem
{
   struct Task
   {
      std::promise<bool> Result;
      std::function<void()> Action;
   };

   class alignas(CacheLineSize) WorkStealingQueue // Eliminate fake sharing.
   {
   private:
      // BACK(Enter) >>>>>> FRONT(Leave)
      std::deque<Task> taskQueue;
      std::mutex mute;

   public:
      WorkStealingQueue()
      {
         //...
      }

      bool IsEmpty()
      {
         std::lock_guard<std::mutex> lock(mute);
         return taskQueue.empty();
      }

      std::future<bool> Push(std::function<void()> job)
      {
         if (!job)
         {
            std::promise<bool> dumyPromise;
            dumyPromise.set_value(false);
            return dumyPromise.get_future();
         }
         std::lock_guard<std::mutex> lock(mute);
         taskQueue.emplace_back(Task{ std::promise<bool>{}, std::move(job) });
         return taskQueue.back().Result.get_future();
      }

      bool PopOrSteal(Task& task, const int32_t threadIdx);
   };

   // Used by the main thread.
   std::array<std::atomic<bool>, ArraySize> StopTokens{};
   std::array<WorkStealingQueue, ArraySize> WSQueues{};
   std::vector<std::thread> Workers{};

   bool WorkStealingQueue::PopOrSteal(Task& task, const int32_t threadIdx)
   {
      std::unique_lock<std::mutex> lock(mute);
      if (taskQueue.empty() == false) // Work
      {
         task = std::move(taskQueue.front());
         taskQueue.pop_front();
         return true;
      }
      else // Steal
      {
         // Don't access current queue now, unlock it.
         lock.unlock();
         for (int32_t i = 0; i < WorkerThreadCount; i++)
         {
            if (i == threadIdx) continue;

            // Try stealing
            {
               WorkStealingQueue& victim = WSQueues[i];
               std::lock_guard<std::mutex> lock2(victim.mute);
               if (victim.taskQueue.empty()) continue;
               task = std::move(victim.taskQueue.back());
               victim.taskQueue.pop_back();
               return true;
            }
         }
      }
      return false;
   }

   // Worker thread.
   void Worker(const std::atomic<bool>& stop_token, const int32_t threadIdx)
   {
      WorkStealingQueue& queue = WSQueues[threadIdx];
      Task task;
      while (true)
      {
         // Simulate the worst situation to validate the MT design.
         //std::this_thread::sleep_for(std::chrono::milliseconds(1));

         if (IsStopped(stop_token)) return;
         if (queue.PopOrSteal(task, threadIdx)) // Get a job
         {
            // *** CORE WORKLOAD ***
            try
            {
               task.Action();
               task.Result.set_value(true);
            }
            catch (...)
            {
               //task.Result.set_exception(std::current_exception());
               task.Result.set_value(false);
            }
         }
         else // Delay
         {
            SpinLoopHint();
         }
      }
   }

   inline void Initialize(const int32_t threadCount)
   {
      WorkerThreadCount = threadCount;
      // Activate workers.
      for (int32_t i = 0; i < threadCount; i++)
      {
         Workers.emplace_back(Worker, std::ref(StopTokens[i]), i);
      }
   }

   inline void Flush(std::future<bool>* futures, int32_t count)
   {
      for (int32_t i = 0; i < count; i++)
      {
         futures[i].get();
      }
   }

   // Please flush queues before termination !!
   inline void Terminate()
   {
      // Stop
      for (int32_t i = 0; i < WorkerThreadCount; i++)
      {
         RequestStop(StopTokens[i]);
         Workers[i].join();
      }
   }
}

using namespace TeslaMT;

namespace Demo
{
   constexpr int32_t JobNum = 1000;
   int32_t SimpleResult[JobNum]{};
   std::future<bool> Futures[JobNum]{};
   std::mutex mute;

   bool ValidateResult()
   {
      std::lock_guard lock(mute);
      for (int32_t i = 0; i < JobNum; i++)
      {
         if (SimpleResult[i] == 0) return false;
      }
      return true;
   }

   void OneJob(const int32_t jobIdx, const int32_t threadIdx)
   {
      int32_t integer = std::max(1, threadIdx + 1);
      integer *= integer;
      integer /= WorkerThreadCount;
      integer = std::max(1, integer);
      std::lock_guard lock(mute);
      SimpleResult[jobIdx] = integer;
   }
}

void mainTeslaJobSystem()
{
   int32_t threadNum = 8;

   std::cout << "Tesla Job System Demo" << std::endl;
   std::cout << "THREAD_NUM = " << threadNum << std::endl;
   std::cout << "JOB_NUM = " << Demo::JobNum << std::endl;

   int32_t round = 0;
   JobSystem::Initialize(threadNum);

   while (true)
   {
      round++;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      // 1. Reset
      {
         std::lock_guard lock(Demo::mute);
         for (int32_t i = 0; i < Demo::JobNum; i++)
         {
            Demo::SimpleResult[i] = 0;
         }
      }
      // 2. Push jobs
      for (int32_t i = 0; i < Demo::JobNum; i++)
      {
         int32_t workerIdx = i % WorkerThreadCount;
         Demo::Futures[i] = JobSystem::WSQueues[workerIdx].Push([=] { Demo::OneJob(i, workerIdx); });
      }
      // 3. Check
      JobSystem::Flush(Demo::Futures, Demo::JobNum);
      std::cout << "ROUND = " << round << ", RESULT = " << (Demo::ValidateResult() ? "True" : "False") << std::endl;
      if (round == 10) break;
   }

   JobSystem::Terminate();
}