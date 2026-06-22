<img src="sticker.jpg" width="100" height="100"></img>
## LeetCode C++ Template Solution | LeetCode C++ 模板工程

A C++ template solution to manage multiple LeetCode answers simultaneously. 

No need to include any std headers and write the "std::" prefix.

一个C++模板工程用于管理多个LeetCode答案。

不需要包含任何 std 头文件和写 “std::” 前缀。

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
External linkage and macro designs. You can investigate them in LeetCodeTemplate.cpp.

外部链接和宏设计。你可以在 LeetCodeTemplate.cpp 中观察它们的设计。
