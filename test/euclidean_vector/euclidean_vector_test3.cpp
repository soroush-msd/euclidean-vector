#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

// <<Rationale>>
// for at() functions, I used at to access different elements of ev and then compared
// them with the expected values of the elements in the object.
// fot non-const at(), I also modified the values of the objects, and then compared each
// element with the new values. with this approach I made sure that I can access the elements
// correctly and modify them as its expected behaviour.
// for dimensions, I created a few objects and then compared the dimension of each object
// by comparing dimensions() and hardcoding their actual dimensions to make sure the output
// of the function is as expected.
// I also check wherever an exception might be thrown according to spec and I compared
// them with the actual hardcoded expected message for each exception accordingly.

TEST_CASE("Part 3. Member Functions") {
	SECTION("Const at()") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto const ev2 =
		   comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};

		CHECK(ev1.at(0) == Approx(4.0));
		CHECK(ev1.at(1) == Approx(4.0));

		CHECK(ev2.at(0) == Approx(1.1));
		CHECK(ev2.at(1) == Approx(2.2));
		CHECK(ev2.at(2) == Approx(3.3));
		CHECK(ev2.at(3) == Approx(4.4));
		CHECK(ev2.at(4) == Approx(0.1322));
		CHECK(ev2.at(5) == Approx(4.23432));
		CHECK(ev2.at(6) == Approx(2112.3));
		CHECK(ev2.at(7) == Approx(64.2123));

		CHECK_THROWS_WITH(ev1.at(-5), "Index -5 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(ev2.at(100), "Index 100 is not valid for this euclidean_vector object");
	}

	SECTION("Non-const at()") {
		auto ev1 = comp6771::euclidean_vector(4, 4.0);
		ev1.at(0) = 5.34;
		ev1.at(1) = 3.567;
		ev1.at(2) = 0.7249;
		ev1.at(3) = 3534345.00000345;

		CHECK(ev1.at(0) == Approx(5.34));
		CHECK(ev1.at(1) == Approx(3.567));
		CHECK(ev1.at(2) == Approx(0.7249));
		CHECK(ev1.at(3) == Approx(3534345.00000345));

		CHECK_THROWS_WITH(ev1.at(43) = 4.3, "Index 43 is not valid for this euclidean_vector object");
	}

	SECTION("Dimensions") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector{};
		auto ev3 = comp6771::euclidean_vector(0, 0.0);
		auto const ev4 =
		   comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};

		CHECK(ev1.dimensions() == 2);
		CHECK(ev2.dimensions() == 1);
		CHECK(ev3.dimensions() == 0);
		CHECK(ev4.dimensions() == 8);
	}
}