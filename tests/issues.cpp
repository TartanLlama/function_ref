#include "catch.hpp"
#include <tl/function_ref.hpp>

TEST_CASE("Issue #2") {
	const auto lam = [](int ) {};
	tl::function_ref<void(int)> ref = lam;
	(void)ref;
}