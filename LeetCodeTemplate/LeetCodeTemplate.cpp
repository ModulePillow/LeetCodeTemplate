//////////////////////////////////////////////

#define SolutionID 0

// Quick Tutorial:
// 1 Set the SolutionID here.
// 2 Implement ur external function at **any** .cpp file (term: a TU): void main<SolutionID>();
// 3 Debug ur program.
//
//////////////////////////////////////////////

#define Concat(x, y) x##y

#define RunSolution(id) \
void Concat(main, id)(); \
Concat(main, id)();

int main()
{
   RunSolution(SolutionID);
}

// An example. Notice that u don't need to include std headers since stdc++.h was included
// implictly (C/C++ > Advanced > Forced Include File), nor do you need the "std::" prefix.
//
void main0()
{
   vector<string> strings{ "Hello", ",", "world", "!"};
   for(auto& str : strings)
   {
      cout << str << " ";
   }
}