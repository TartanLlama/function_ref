#include "catch.hpp"
#include <tl/function_ref.hpp>
#include <type_traits>

void foo(){}
struct bar {
    void baz(){}
};

TEST_CASE("Constructors", "[constructors]") {
    tl::function_ref<void(void)> fr1 = []{};
    tl::function_ref<void(void)> fr2 = foo;
    tl::function_ref<void(bar)> fr3 = &bar::baz;

    // Silence warnings
    (void)fr1;
    (void)fr2;
    (void)fr3;
}

using FR = tl::function_ref<void(void)>;
static_assert(std::is_trivially_constructible<FR, FR&>::value, "");
static_assert(std::is_trivially_constructible<FR, const FR&>::value, "");
static_assert(std::is_trivially_constructible<FR, FR&&>::value, "");
