#include "catch.hpp"
#include <tl/function_ref.hpp>
#include <type_traits>

void f(){}
struct b {
    void baz(){}
    void qux(){}    
};

TEST_CASE("Assignment", "[assignment]") {
    {
        tl::function_ref<void(void)> fr = f;
        fr = []{};
    }

    {
        tl::function_ref<void(b)> fr = &b::baz;
        fr = &b::qux;
    }
}

using FR = tl::function_ref<void(void)>;
static_assert(std::is_trivially_assignable<FR, FR&>::value, "");
static_assert(std::is_trivially_assignable<FR, const FR&>::value, "");
static_assert(std::is_trivially_assignable<FR, FR&&>::value, "");
