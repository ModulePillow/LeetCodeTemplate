//////////////////////////////////////////////

#define SolutionID 0

// Quick Tutorial:
// 1 Set the SolutionID here.
// 2 Implement ur external function at **any** .cpp file (term: a TU): void main<SolutionID>();
// 3 Debug ur program.
// 
// 教程:
// 1 在这里设置 SolutionID。
// 2 在 **任意** .cpp 文件（术语：翻译单元）中实现： void main<SolutionID>()；
// 3 去调试。
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
// 例子。注意你不用包含 std 头文件，因为 stdc++.h 已被隐式包含
// （C/C++ > Advanced > Forced Include File）；也无需 "std" 前缀。
//
void main0()
{
   vector<string> strings{ "Hello", ",", "world", "!"};
   for(auto& str : strings)
   {
      cout << str << " ";
   }
}