#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

// <<Rationale>>
// for norm and dot functions, I created euclidean vectors and then compared
// the value returned by calling the functions to their expected value using Approx.
// for unit, instead of checking each element one by one this time, I used << operator
// as I think it would be more readable to do so rather than checking element by element.
// Then I compared the output string of the function with its expecetd string value.
// so by calculating their expected values with calculator and then comparing those values
// with values outputted from function, I made sure that the functions work as they're supposed to.

TEST_CASE("Part 6. Utility Functions") {
	SECTION("Norm") {
		auto const ev1 = comp6771::euclidean_vector(1, 10.0);
		CHECK(comp6771::euclidean_norm(ev1) == Approx(10));

		auto const ev2 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
		CHECK(comp6771::euclidean_norm(ev2) == Approx(3.74165));

		auto const ev3 = comp6771::euclidean_vector{0.0};
		CHECK(comp6771::euclidean_norm(ev3) == Approx(0.0));

		auto const ev4 = comp6771::euclidean_vector(2, 20.0);
		CHECK(comp6771::euclidean_norm(ev4) == Approx(28.2842));
	}

	SECTION("Unit") {
		auto const ev1 = comp6771::euclidean_vector(4, 10.0);
		auto const ev2 = comp6771::unit(ev1);
		auto oss = std::ostringstream{};
		oss << ev2;
		CHECK(oss.str() == "[0.5 0.5 0.5 0.5]");

		auto const ev3 = comp6771::euclidean_vector(0);
		CHECK_THROWS_WITH(comp6771::unit(ev3),
		                  "euclidean_vector with no dimensions does not have a unit vector");

		auto const ev4 = comp6771::euclidean_vector(5, 0.0);
		CHECK_THROWS_WITH(comp6771::unit(ev4),
		                  "euclidean_vector with zero euclidean normal does not have a unit vector");

		auto const ev5 = comp6771::euclidean_vector(4, -10.0);
		auto const ev6 = comp6771::unit(ev5);
		auto oss2 = std::ostringstream{};
		oss2 << ev6;
		CHECK(oss2.str() == "[-0.5 -0.5 -0.5 -0.5]");
	}

	SECTION("Dot") {
		auto ev1 = comp6771::euclidean_vector(3, 10.0);
		auto ev2 = comp6771::euclidean_vector(3, 10.0);
		auto ev3 = double{comp6771::dot(ev1, ev2)};
		CHECK(ev3 == Approx(300));

		ev1 /= 2;
		ev2 /= 2;
		ev3 = double{comp6771::dot(ev1, ev2)};
		CHECK(ev3 == Approx(75));

		auto ev4 = comp6771::euclidean_vector(1, 4.0);
		auto ev5 = comp6771::euclidean_vector(5, 10.0);
		CHECK_THROWS_WITH(double{comp6771::dot(ev4, ev5)},
		                  "Dimensions of LHS(1) and RHS(5) do not match");
	}
}