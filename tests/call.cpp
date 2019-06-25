#include "catch.hpp"
#include <tl/function_ref.hpp>

namespace {
bool f_called = false;
void f(){f_called=true;}
struct b {
    bool baz_called = false;
    void baz(){baz_called=true;}
    bool qux_called = false;
    void qux(){qux_called=true;}    
};
}

TEST_CASE("Call", "[call]") {
    {
        tl::function_ref<void(void)> fr = f;
        fr();
        REQUIRE(f_called);
    }

    {
        b o;
        auto x = &b::baz;
        tl::function_ref<void(b&)> fr = x;
        fr(o);
        REQUIRE(o.baz_called);        
        x = &b::qux;
        fr = x;
        fr(o);
        REQUIRE(o.qux_called);                
    }

    {
        auto x = []{ return 42; };
        tl::function_ref<int()> fr = x;
        REQUIRE(fr() == 42);
    }

    {
        int i = 0;
        auto x = [&i]{ i = 42; };
        tl::function_ref<void()> fr = x;
        fr();
        REQUIRE(i == 42);
    }    
}
