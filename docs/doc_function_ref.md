# Header file `function_ref.hpp`<a id="function_ref.hpp"></a>

<pre><code class="language-cpp">#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_HPP</a>

#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_VERSION_MAJOR</a>

#define <a href='doc_function_ref.html#function_ref.hpp'>TL_FUNCTION_REF_VERSION_MINOR</a>

namespace <a href='doc_function_ref.html#function_ref.hpp'>tl</a>
{
    namespace <a href='doc_function_ref.html#function_ref.hpp'>detail</a>
    {
        template &lt;class T&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>remove_const_t</a> = typename std::remove_const&lt;T&gt;::type;
        
        template &lt;class T&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>remove_reference_t</a> = typename std::remove_reference&lt;T&gt;::type;
        
        template &lt;class T&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>decay_t</a> = typename std::decay&lt;T&gt;::type;
        
        template &lt;bool E, class T = void&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>enable_if_t</a> = typename std::enable_if&lt;E, T&gt;::type;
        
        template &lt;bool B, class T, class F&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>conditional_t</a> = typename std::conditional&lt;B, T, F&gt;::type;
        
        template &lt;typename Fn, typename ... Args, typename = enable_if_t&lt;std::is_member_pointer&lt;decay_t&lt;Fn&gt;&gt;::value&gt;, int=0&gt;
        constexpr decltype(std::mem_fn(f)(std::forward&lt;Args&gt;(args)...)) <a href='doc_function_ref.html#function_ref.hpp'>invoke</a>(Fn&amp;&amp; f, Args&amp;&amp;... args) noexcept(noexcept(std::mem_fn(f)(std::forward&lt;Args&gt;(args)...)));
        
        template &lt;typename Fn, typename ... Args, typename = enable_if_t&lt;!std::is_member_pointer&lt;decay_t&lt;Fn&gt;&gt;{}&gt;&gt;
        constexpr decltype(std::forward&lt;Fn&gt;(f)(std::forward&lt;Args&gt;(args)...)) <a href='doc_function_ref.html#function_ref.hpp'>invoke</a>(Fn&amp;&amp; f, Args&amp;&amp;... args) noexcept(noexcept(std::forward&lt;Fn&gt;(f)(std::forward&lt;Args&gt;(args)...)));
        
        template &lt;class F, class ... Us&gt;
        struct <a href='doc_function_ref.html#function_ref.hpp'>invoke_result_impl&lt;F, decltype(invoke(std::declval&lt;F&gt;(), std::declval&lt;Us&gt;()...), void()), Us...&gt;</a>;
        
        template &lt;class F, class ... Us&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>invoke_result</a> = invoke_result_impl&lt;F, void, Us...&gt;;
        
        template &lt;class F, class ... Us&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>invoke_result_t</a> = typename invoke_result&lt;F, Us...&gt;::type;
        
        template &lt;class, class R, class F, class ... Args&gt;
        struct <a href='doc_function_ref.html#function_ref.hpp'>is_invocable_r_impl</a>;
        
        template &lt;class R, class F, class ... Args&gt;
        struct <a href='doc_function_ref.html#function_ref.hpp'>is_invocable_r_impl&lt;typename std::is_same&lt;invoke_result_t&lt;F, Args...&gt;, R&gt;::type, R, F, Args...&gt;</a>;
        
        template &lt;class R, class F, class ... Args&gt;
        using <a href='doc_function_ref.html#function_ref.hpp'>is_invocable_r</a> = <a href='doc_function_ref.html#function_ref.hpp'>is_invocable_r_impl&lt;std::true_type, R, F, Args...&gt;</a>;
    }
    
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

Specialization for function types.

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
