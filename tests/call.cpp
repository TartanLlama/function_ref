#include "catch.hpp"
#include "function_ref.hpp"

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
        tl::function_ref<void(b&)> fr = &b::baz;
        fr(o);
        REQUIRE(o.baz_called);        
        fr = &b::qux;
        fr(o);
        REQUIRE(o.qux_called);                
    }

    {
        tl::function_ref<int()> fr = []{ return 42; };
        REQUIRE(fr() == 42);
    }

    {
        int i = 0;
        tl::function_ref<void()> fr = [&i]{ i = 42; };
        fr();
        REQUIRE(i == 42);
    }    
}
