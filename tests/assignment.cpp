#include "catch.hpp"
#include "function_ref.hpp"

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
