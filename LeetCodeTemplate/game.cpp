#include <iostream>
#include "client.h"
#include "game.h"


Client* MultithreadedGame::onJoin()
{
   // std::cout << "This is debug output" << std::endl;
   std::lock_guard<std::mutex> lock(playersMute);
   MultithreadedClient client;
   Client* newClient = &players.emplace_back(std::move(client));
   return newClient;
}

void MultithreadedGame::onGetItem(Client* clientPtr, std::string_view name,
   int amount)
{
   // Validation checks
   if (!clientPtr || name.size() == 0 || amount <= 0) return;

   MultithreadedClient* client = dynamic_cast<MultithreadedClient*>(clientPtr);
   if (client == nullptr) return;

   // Get action
   std::lock_guard<std::mutex> lock(client->bagMute);
   auto itr = client->bag.find(std::string(name));
   if(itr != client->bag.end())
   {
      itr->second += amount;
   }
   else
   {
      client->bag[std::string(name)] = amount;
   }

}

void MultithreadedGame::onDropItem(Client* clientPtr, std::string_view name,
   int amount)
{
   // Validation checks
   if (!clientPtr || name.size() == 0 || amount <= 0) return;

   MultithreadedClient* client = dynamic_cast<MultithreadedClient*>(clientPtr);
   if (client == nullptr) return;

   // Drop action
   std::lock_guard<std::mutex> lock(client->bagMute);
   auto itr = client->bag.find(std::string(name));
   if(itr != client->bag.end())
   {
      if (itr->second > amount)
      {
         itr->second -= amount;
      }
      else
      {
         client->bag.erase(itr);
      }
   }
}

void MultithreadedGame::onGiveItem(Client* fromClientPtr, Client* toClientPtr,
   std::string_view name, int amount)
{
   // Validation checks
   if (!fromClientPtr || !toClientPtr || name.size() == 0 || amount <= 0) return;

   // Actions
   onDropItem(fromClientPtr, name, amount);
   onGetItem(toClientPtr, name, amount);
}

void MultithreadedGame::onLeave(Client* clientPtr)
{
   // Validation checks
   if (!clientPtr) return;

   std::lock_guard<std::mutex> lock(playersMute);
   auto itr = std::find_if(players.begin(), players.end(), [&](const Client& client) { return &client == clientPtr; });
   if (itr != players.end())
   {
      players.erase(itr);
   }
}

std::size_t MultithreadedGame::getClientCount() const
{
   std::lock_guard<std::mutex> lock(playersMute);
   return players.size();
}