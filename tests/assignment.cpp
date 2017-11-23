#include "catch.hpp"
#include "function_ref.hpp"

void f(){}
struct b {
    void baz(){}
};

TEST_CASE("Assignment", "[assignment]") {
    {
        tl::function_ref<void(void)> fr;

        fr = f;
        REQUIRE(fr);

        fr = nullptr;
        REQUIRE(!fr);

        fr = []{};
        REQUIRE(fr);

        fr = nullptr;
        REQUIRE(!fr);
    }

    {
        tl::function_ref<void(b)> fr;

        fr = &b::baz;;
        REQUIRE(fr);

        fr = nullptr;
        REQUIRE(!fr);
    }
}
