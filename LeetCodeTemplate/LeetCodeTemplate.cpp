//////////////////////////////////////////////
//
#define SolutionID 0
//
// Quick Tutorial:
// 1 Set the SolutionID.
// 2 Implement ur external function at any .cpp file (term: a translation unit): void main<SolutionID>();
// 3 Debug ur program.
// 
// 快速教程:
// 1 设置 SolutionID。
// 2 在任意 .cpp 文件（术语：翻译单元）实现: void main<SolutionID>();
// 3 调试。
//////////////////////////////////////////////

#define Concat(x, y) x##y

#define RunSolution(id) \
void Concat(main, id)(); \
Concat(main, id)();

int main()
{
   RunSolution(SolutionID);
}

// An example. Notice that u don't need to include std headers since stdc++.h exists, nor do you need the "std::" prefix.
// 一个例子。注意，你不需要包含 std 头文件，因为 stdc++.h 已存在；也无需 "std" 前缀。
void main0()
{
   vector<string> strings{ "Hello", "world", "."};
   for(auto& str : strings)
   {
      cout << str << " ";
   }
}