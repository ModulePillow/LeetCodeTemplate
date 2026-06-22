// A custom version of stdc++.h for online coding.
#pragma once

#if defined(_MSVC_LANG)
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif

using namespace std;

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cfloat>
#include <climits>
#include <csetjmp>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>

#if CPP_VERSION >= 201103L
#include <cstdint>
#if CPP_VERSION < 201703L
#include <ciso646>
#endif
#endif

// C++
// #include <bitset>
// #include <complex>
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <numeric>
#include <typeinfo>
#include <utility>

#if CPP_VERSION >= 201103L
#include <array>
#include <atomic>
#include <initializer_list>
#include <ratio>
#include <scoped_allocator>
#include <tuple>
#include <typeindex>
#include <type_traits>
#endif

#if CPP_VERSION >= 201402L
#endif

#if CPP_VERSION >= 201703L
#include <any>
// #include <execution>
#include <optional>
#include <variant>
#include <string_view>
#endif

#if CPP_VERSION >= 202002L
#include <bit>
#include <compare>
#include <concepts>
#include <numbers>
#include <ranges>
#include <span>
#include <source_location>
#include <version>
#if __cpp_impl_coroutine
# include <coroutine>
#endif
#endif

#if CPP_VERSION > 202002L
#include <expected>
#include <stdatomic.h>
#endif

#if _GLIBCXX_HOSTED
// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if CPP_VERSION >= 201103L
#include <cfenv>
#include <cinttypes>
#include <cstdint>
#include <cuchar>
#if CPP_VERSION < 201703L
#include <ccomplex>
#include <cstdalign>
#include <cstdbool>
#include <ctgmath>
#endif
#endif

// C++
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if CPP_VERSION >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if CPP_VERSION >= 201402L
#include <shared_mutex>
#endif

#if CPP_VERSION >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <optional>
#include <memory_resource>
#include <variant>
#endif

#if CPP_VERSION >= 202002L
#include <barrier>
#include <bit>
#include <compare>
#include <concepts>
#include <format>
#include <latch>
#include <numbers>
#include <ranges>
#include <span>
#include <stop_token>
#include <semaphore>
#include <source_location>
#include <syncstream>
#include <version>
#endif

#if CPP_VERSION > 202002L
#include <expected>
#include <flat_map>
#include <flat_set>
#include <generator>
#include <print>
#include <spanstream>
#include <stacktrace>
#include <stdatomic.h>
#include <stdfloat>
#endif

#if CPP_VERSION > 202302L
#include <text_encoding>
#include <stdbit.h>
#include <stdckdint.h>
#endif

#endif // HOSTED