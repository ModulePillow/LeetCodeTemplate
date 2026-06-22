void mainRegex()
{
   vector<string> cases = {
      "http://a.com/badURL",
      "https://x.com/A1oneSKy",
      "https://www.udemy.com/browse/certification/aws-certifications/",
      "https://arena.ai/leaderboard",
      "https://cmake.org/cmake/help/latest/",
      "https://moegirl.icu/Mainpage",
   };

   regex pattern { R"(https:\/\/(.*)$)" };

   int32_t count = 0;
   for (const auto& url : cases)
   {
      smatch match;
      if (regex_search(url, match, pattern))
      {
         
         cout << "Result" << ++count << ": " << match.str(1) << endl;
      }
   }
}