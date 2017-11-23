#include "catch.hpp"
#include "function_ref.hpp"

void foo(){}
struct bar {
    void baz(){}
};

TEST_CASE("Constructors", "[constructors]") {
    {
        tl::function_ref<void(void)> fr;
        REQUIRE(!fr);
    }

    {
        tl::function_ref<void(void)> fr = nullptr;
        REQUIRE(!fr);
    }    

    {
        tl::function_ref<void(void)> fr = []{};
        REQUIRE(fr);
    }

    {
        tl::function_ref<void(void)> fr = foo;
        REQUIRE(fr);
    }        

    {
        tl::function_ref<void(bar)> fr = &bar::baz;
        REQUIRE(fr);
    }            
}
