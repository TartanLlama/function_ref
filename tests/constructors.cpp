#include "catch.hpp"
#include "function_ref.hpp"

void foo(){}
struct bar {
    void baz(){}
};

TEST_CASE("Constructors", "[constructors]") {
    tl::function_ref<void(void)> fr1 = []{};
    tl::function_ref<void(void)> fr2 = foo;
    tl::function_ref<void(bar)> fr3 = &bar::baz;
}
