#pragma once

//#include "base/client.h"

class Client
{
public:
   virtual ~Client() = default;
   virtual std::optional<int> getItemCount(std::string_view name) { return std::nullopt; };
};

class MultithreadedClient : public Client {
public:
   /**
    * Find an item in the bag, and return its count.
    * Returns if the item is missing.
    */
   std::optional<int> getItemCount(std::string_view name) override;

public:
   std::unordered_map<std::string, uint32_t> bag;
   mutable std::mutex bagMute;

//private:
//   std::thread Worker;
//   TeslaMT::JobSystem::WorkStealingQueue WSQueue;
};