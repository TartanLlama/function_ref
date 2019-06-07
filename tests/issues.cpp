#include "catch.hpp"
#include "function_ref.hpp"

TEST_CASE("Issue #2") {
	const auto lam = [](int ) {};
	tl::function_ref<void(int)> ref = lam;
	(void)ref;
}

struct Fruit {};
struct Apple : Fruit {};

Apple* getApple() { return nullptr; }

tl::function_ref<Fruit* ()> bar()
{
  return getApple;
}

TEST_CASE("Issue #9") {
  bar();
}