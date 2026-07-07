#include "client.h"

std::optional<int> MultithreadedClient::getItemCount(std::string_view name)
{
   if(name.empty()) return std::nullopt;
   std::lock_guard<std::mutex> lock(bagMute);
   auto itr = bag.find(std::string(name));
   if(itr == bag.end()) return std::nullopt;
   else
   {
      return itr->second;
   }
}