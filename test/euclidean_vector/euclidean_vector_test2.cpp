#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

// <<Rationale>>
// For operators, I created two or three euclidean vectors in most cases, then changed the value
// of one object in respect to the other ones, and then compared the results using Approx and
// == operator accordingly.
// for copy/move assignments, I copied/moved one vector to the other and then checked if
// they're equal to the initial state of the copied from/moved from euclidean vector.
// for -=,+=,*=,/=, I checked the result by checking enforcing each operation to
// individual values and use Approx to ensure the results are as expected.
// for conversions, I created a vector or list of the same values to the euclidean vector,
// then I compared the result vector/list from conversion and used == operator to check
// they are equal to their original container. this ensures the output result is as expected.
// also exceptions are checked according to the spec.
// I also check wherever an exception might be thrown according to spec and I compared
// them with the actual hardcoded expected message for each exception accordingly.

TEST_CASE("Part 2. Operations") {
	SECTION("Copy Assignment") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto const ev2 =
		   comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};
		ev1 = ev2;

		CHECK(ev1.dimensions() == 8);
		CHECK(ev1 == ev2);
	}

	SECTION("Move Assignment") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};
		auto const ev3 =
		   comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};
		ev1 = std::move(ev2);

		CHECK(ev1.dimensions() == 8);
		CHECK(ev1 == ev3);
		CHECK(ev2.dimensions() == 0);
	}

	SECTION("Const []") {
		auto const ev1 = comp6771::euclidean_vector(2, 2.34523004354);
		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);

		CHECK(ev1[0] == Approx(ev1.at(0)));
		CHECK(ev1[1] == Approx(ev1.at(1)));

		CHECK(ev2[0] == Approx(ev2.at(0)));
		CHECK(ev2[1] == Approx(ev2.at(1)));
	}

	SECTION("Non-const []") {
		auto ev1 = comp6771::euclidean_vector(2, 2.34523004354);
		ev1[0] = 4.2123;
		ev1[1] = 0.232032768;

		CHECK(ev1[0] == Approx(4.2123));
		CHECK(ev1[1] == Approx(0.232032768));
	}

	SECTION("Unary Plus") {
		auto const ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);
		auto ev3 = +ev1;
		ev2 = +ev1;

		CHECK(ev3.dimensions() == ev1.dimensions());
		CHECK(ev1 == ev3);

		CHECK(ev2.dimensions() == ev1.dimensions());
		CHECK(ev1 == ev2);
	}

	SECTION("Negation") {
		auto const ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);
		auto ev3 = -ev1;
		ev2 = -ev1;

		CHECK(ev3.dimensions() == ev1.dimensions());
		CHECK(ev3.at(0) == Approx(-4.0));
		CHECK(ev3.at(1) == Approx(-4.0));

		CHECK(ev2.dimensions() == ev1.dimensions());
		CHECK(ev2.at(0) == Approx(-4.0));
		CHECK(ev2.at(1) == Approx(-4.0));

		auto const actual = comp6771::euclidean_vector{-6, 1};
		auto const expected = comp6771::euclidean_vector{6, -1};
		CHECK(expected == -actual);
	}

	SECTION("Compound Addition") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);
		auto ev3 = comp6771::euclidean_vector{-6, 1, 5.372, 0.45};
		auto zeroV = comp6771::euclidean_vector{0.0, 0.0};

		ev2 += ev1;
		CHECK(ev2.dimensions() == ev1.dimensions());
		CHECK(ev2.at(0) == Approx(4.0 + 2.34523004354));
		CHECK(ev2.at(1) == Approx(4.0 + 2.34523004354));

		ev1 -= zeroV;
		CHECK(ev1.dimensions() == zeroV.dimensions());
		CHECK(ev1.at(0) == Approx(4.0));
		CHECK(ev1.at(1) == Approx(4.0));

		CHECK_THROWS_WITH(ev3 += ev1, "Dimensions of LHS(4) and RHS(2) do not match");
	}

	SECTION("Compound Subtraction") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);
		auto ev3 = comp6771::euclidean_vector{-6, 1, 5.372, 0.45};
		auto zeroV = comp6771::euclidean_vector{0.0, 0.0};

		ev2 -= ev1;
		CHECK(ev2.dimensions() == ev1.dimensions());
		CHECK(ev2.at(0) == Approx(-4.0 + 2.34523004354));
		CHECK(ev2.at(1) == Approx(-4.0 + 2.34523004354));

		ev1 -= zeroV;
		CHECK(ev1.dimensions() == zeroV.dimensions());
		CHECK(ev1.at(0) == Approx(4.0));
		CHECK(ev1.at(1) == Approx(4.0));

		CHECK_THROWS_WITH(ev3 -= ev1, "Dimensions of LHS(4) and RHS(2) do not match");
	}

	SECTION("Compound Multiplication") {
		auto ev1 = comp6771::euclidean_vector(2, 2.34523004354);
		auto scalar = 3;

		ev1 *= scalar;
		CHECK(ev1.dimensions() == 2);
		CHECK(ev1.at(0) == Approx(scalar * 2.34523004354));
		CHECK(ev1.at(1) == Approx(scalar * 2.34523004354));

		auto ev2 = comp6771::euclidean_vector(2, 0.0);
		ev2 *= scalar;
		CHECK(ev2.dimensions() == 2);
		CHECK(ev2.at(0) == Approx(scalar * 0.0));
		CHECK(ev2.at(1) == Approx(scalar * 0.0));
	}

	SECTION("Compound Division") {
		auto ev1 = comp6771::euclidean_vector(2, 2.34523004354);
		auto scalar = 3;

		ev1 /= scalar;
		CHECK(ev1.dimensions() == 2);
		CHECK(ev1.at(0) == Approx(2.34523004354 / scalar));
		CHECK(ev1.at(1) == Approx(2.34523004354 / scalar));

		auto ev2 = comp6771::euclidean_vector(2, 2.34523004354);
		scalar = 0;
		CHECK_THROWS_WITH(ev2 /= scalar, "Invalid vector division by 0");
	}

	SECTION("Vector Type Conversion") {
		auto const ev1 = comp6771::euclidean_vector(5, 2.3452);
		auto v = std::vector{2.3452, 2.3452, 2.3452, 2.3452, 2.3452};
		auto const vf = static_cast<std::vector<double>>(ev1);

		CHECK(vf == v);
	}

	SECTION("List Type Conversion") {
		auto const ev1 = comp6771::euclidean_vector(5, 2.3452);
		auto l = std::list{2.3452, 2.3452, 2.3452, 2.3452, 2.3452};
		auto lf = static_cast<std::list<double>>(ev1);

		CHECK(lf == l);
	}
}