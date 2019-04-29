# function_ref

A lightweight non-owning reference to a callable.

Clang + GCC: [![Linux Build Status](https://travis-ci.org/TartanLlama/function_ref.png?branch=master)](https://travis-ci.org/TartanLlama/function_ref)
MSVC: [![Windows Build Status](https://ci.appveyor.com/api/projects/status/k5x00xa11y3s5wsg?svg=true)](https://ci.appveyor.com/project/TartanLlama/function_ref)

Use `tl::function_ref` instead of `std::function` whenever you don't need to own the callable. The most common case for this is function parameters which aren't stored anywhere:

```cpp
void foo (function_ref<int(int)> func) {
    std::cout << "Result is " << func(21); //42
}

foo([](int i) { return i*2; });
```

Full documentation available [here](https://tl.tartanllama.xyz/).

----------

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png)]("http://creativecommons.org/publicdomain/zero/1.0/")

To the extent possible under law, [Simon Brand](https://twitter.com/TartanLlama) has waived all copyright and related or neighboring rights to the `function_ref` library. This work is published from: United Kingdom.
