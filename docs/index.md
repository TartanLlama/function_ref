# Header file `function_ref.hpp`<a id="function_ref.hpp"></a>

<pre><code class="language-cpp">#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_HPP</a>

#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_VERSION_MAJOR</a>

#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_VERSION_MINOR</a>

namespace <a href='doc_function_ref.html#function_ref.hpp'>tl</a>
{
    template &lt;class R, class ... Args&gt;
    class <a href='doc_function_ref.html#tl::function_ref-R(Args...)-'>function_ref&lt;R(Args...)&gt;</a>;
    
    template &lt;typename R, typename ... Args&gt;
    constexpr void <a href='doc_function_ref.html#tl::swap(function_ref-R(Args...)-&,function_ref-R(Args...)-&)'>swap</a>(function_ref&lt;R(Args...)&gt;&amp; lhs, function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;
}</code></pre>

## Class template `tl::function_ref<R(Args...)>`<a id="tl::function_ref-R(Args...)-"></a>

<pre><code class="language-cpp">template &lt;class R, class ... Args&gt;
class function_ref&lt;R(Args...)&gt;
{
public:
    constexpr <a href='doc_function_ref.html#tl::function_ref-R(Args...)-'>function_ref</a>() noexcept = delete;
    
    constexpr <a href='doc_function_ref.html#tl::function_ref-R(Args...)-::function_ref(constfunction_ref-R(Args...)-&)'>function_ref</a>(const function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept = default;
    
    template &lt;typename F&gt; constexpr function_ref(F &amp;&amp;f) noexcept
    
    constexpr function_ref&lt;R(Args...)&gt;&amp; <a href='doc_function_ref.html#tl::function_ref-R(Args...)-::operator=(Args...,constfunction_ref-R(Args...)-&)'>operator=</a>(Args..., const function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;
    
    template &lt;typename F&gt; constexpr function_ref &amp;operator=(F &amp;&amp;f) noexcept;
    
    constexpr void <a href='doc_function_ref.html#tl::function_ref-R(Args...)-::swap(function_ref-R(Args...)-&)'>swap</a>(function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;
    
    R <a href='doc_function_ref.html#tl::function_ref-R(Args...)-::operator()(Args...)const'>operator()</a>(Args... args) const;
};</code></pre>

A lightweight non-owning reference to a callable.

Example usage:

``` cpp
void foo (function_ref<int(int)> func) {
    std::cout << "Result is " << func(21); //42
}

foo([](int i) { return i*2; });
```

### Copy constructor `tl::function_ref<R(Args...)>::function_ref`<a id="tl::function_ref-R(Args...)-::function_ref(constfunction_ref-R(Args...)-&)"></a>

<pre><code class="language-cpp">constexpr function_ref(const function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept = default;</code></pre>

Creates a `function_ref` which refers to the same callable as `rhs`.

### Function template `tl::function_ref<R(Args...)>::function_ref`<a id="tl::function_ref-R(Args...)-::function_ref(F&&)"></a>

<pre><code class="language-cpp">template &lt;typename F&gt; constexpr function_ref(F &amp;&amp;f) noexcept</code></pre>

Constructs a `function_ref` referring to `f`.

### Assignment operator `tl::function_ref<R(Args...)>::operator=`<a id="tl::function_ref-R(Args...)-::operator=(Args...,constfunction_ref-R(Args...)-&)"></a>

<pre><code class="language-cpp">constexpr function_ref&lt;R(Args...)&gt;&amp; operator=(Args..., const function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;</code></pre>

Makes `*this` refer to the same callable as `rhs`.

### Assignment operator `tl::function_ref<R(Args...)>::operator=`<a id="tl::function_ref-R(Args...)-::operator=(Args...,F&&)"></a>

<pre><code class="language-cpp">template &lt;typename F&gt; constexpr function_ref &amp;operator=(F &amp;&amp;f) noexcept;</code></pre>

Makes `*this` refer to `f`.

### Function `tl::function_ref<R(Args...)>::swap`<a id="tl::function_ref-R(Args...)-::swap(function_ref-R(Args...)-&)"></a>

<pre><code class="language-cpp">constexpr void swap(function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;</code></pre>

Swaps the referred callables of `*this` and `rhs`.

### Function call operator `tl::function_ref<R(Args...)>::operator()`<a id="tl::function_ref-R(Args...)-::operator()(Args...)const"></a>

<pre><code class="language-cpp">R operator()(Args... args) const;</code></pre>

Call the stored callable with the given arguments.

-----

## Function template `tl::swap`<a id="tl::swap(function_ref-R(Args...)-&,function_ref-R(Args...)-&)"></a>

<pre><code class="language-cpp">template &lt;typename R, typename ... Args&gt;
constexpr void swap(function_ref&lt;R(Args...)&gt;&amp; lhs, function_ref&lt;R(Args...)&gt;&amp; rhs) noexcept;</code></pre>

Swaps the referred callables of `lhs` and `rhs`.

-----
