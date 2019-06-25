#include "catch.hpp"
#include <tl/function_ref.hpp>

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

void foo(const tl::function_ref<int(const std::vector<int>)>& func) {
  REQUIRE(func({ 12 }) == 144);
}

TEST_CASE("Issue #10") {
  int z = 12;
  auto f = [&](const std::vector<int> i) { return i[0] * z; };
  foo(f);
}