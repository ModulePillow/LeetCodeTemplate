<img src="sticker.jpg" width="100" height="100"></img>
## LeetCode C++ Template Solution

A C++ template solution to manage multiple LeetCode answers simultaneously. No need to include any std headers and write the "std::" namespace prefix.


## Example
```cpp
#define SolutionID 0

// Start debugging, main0() will be excuted automatically.
void main0()
{
   vector<string> strings{ "Hello", "world", "."};
   for(auto& str : strings)
   {
      cout << str << " ";
   }
}
```

## How it works

External linkage and macro designs. You can investigate them in LeetCodeTemplate.cpp.

## IDE and Compiler
> IDE: Visual Sudio 2022.
> 
> Compiler: MSVC or Clang. Choose the compiler at *Properties>General>Platform Toolset*. If you prefer Clang, you should install it in the VS Installer first.
