<img src="sticker.jpg" width="100" height="100"></img>
## LeetCode C++ Template Solution | LeetCode C++ 模板工程
一个 C++ 模板工程用于管理多个 LeetCode 答案。不需要 include 任何 std 头文件和写 “std::” 名称前缀。

A C++ template solution to manage multiple LeetCode answers simultaneously. No need to include any std headers and write the "std::" namespace prefix.


## Example | 示例
```cpp
#define SolutionID 0

// Start debugging, main0() will be excuted automatically.
// 开始调试，main0() 会被自动调用。
void main0()
{
   vector<string> strings{ "Hello", "world", "."};
   for(auto& str : strings)
   {
      cout << str << " ";
   }
}
```

## How it works | 工作原理
外部链接和宏设计。你可以在 LeetCodeTemplate.cpp 中观察它们的设计。

External linkage and macro designs. You can investigate them in LeetCodeTemplate.cpp.

## IDE and Compiler | IDE 和编译器
> IDE: Visual Sudio 2022.
> 
> Compiler: MSVC 或 Clang。在 *Properties>General>Platform Toolset* 处选择编译器。如果你想用 Clang, 你应该在 VS Installer 中先安装它。

> IDE: Visual Sudio 2022.
> 
> Compiler: MSVC or Clang. Choose the compiler at *Properties>General>Platform Toolset*. If you prefer Clang, you should install it in the VS Installer first.


