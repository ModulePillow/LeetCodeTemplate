// Find the longest cycle in a diagram.
void mainUnity_06_23()
{
   //...
   vector<int32_t> data{1,2,3,4,5,0};
   int32_t result = 0;

   for (int32_t i = 0; i < data.size(); ++i)
   {
      int32_t next = data[i];
      int32_t length {};

      while(next != -1 && length <= data.size())
      {
         // Find a new node rather than itself.
         ++length;
         if (next == i) break;
         next = data[next];
      }

      // Find the maximum length.
      if (next != -1 && length <= data.size() && length > result) result = length;
   }

   cout << result;
}