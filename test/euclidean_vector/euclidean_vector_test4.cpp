#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

// <<Rationale>>
// for friend functions, I used the same reasoning as previous test files.
// for == and I created similar vectors of the same size and dimension and then
// compared them with ==, expecting to return true as they are equal.
// for !=, I created different vectors, so when comparing with !=, they needed
// to evaluate to true as they are not equal.
// for addition and subtraction, I constructed objects and after doing +/- operation,
// I checked each element by its ecpexted value using approx. so I made sure that
// the +/- operation has been done on each of the elements and the result is as expected.
// for multiply and division, I tested with the same approach by comparing the elements
// with their expected value to enusre the correctness of the operators.
// for output stream, I outputted empty vector, one dimensional vector and multi-dimensional
// vectors, I used == operator to comapre them with the expted string values.
// I also check wherever an exception might be thrown according to spec and I compared
// them with the actual hardcoded expected message for each exception accordingly.

TEST_CASE("Part 4. Friend Functions") {
	SECTION("Equal Operator") {
		auto ev1 = comp6771::euclidean_vector(3, 6.3);
		auto const ev2 = comp6771::euclidean_vector{6.3, 6.3, 6.3};

		std::vector<double> v{6.3, 6.3, 6.3};
		auto ev3 = comp6771::euclidean_vector(v.begin(), v.end());

		CHECK(ev1 == ev2);
		CHECK(ev2 == ev3);
		CHECK(ev1 == ev3);
	}

	SECTION("Not Equal Operator") {
		auto ev1 = comp6771::euclidean_vector(3, 5.3);
		auto const ev2 = comp6771::euclidean_vector{6.3, 6.3, 6.3};
		auto ev3 = comp6771::euclidean_vector{0.0, 0.0, 0.0};
		auto const ev4 = comp6771::euclidean_vector{};

		CHECK(ev1 != ev2);
		CHECK(ev3 != ev4);
		CHECK(ev1 != ev3);
		CHECK(ev2 != ev4);
	}

	SECTION("Addition") {
		auto ev1 = comp6771::euclidean_vector(3, 5.3);
		auto const ev2 = comp6771::euclidean_vector{6.3, 6.3, 6.3};
		auto zeroV = comp6771::euclidean_vector(3, 0.0);

		auto addV1 = ev1 + ev2;
		CHECK(addV1.dimensions() == 3);
		CHECK(addV1.at(0) == Approx(5.3 + 6.3));
		CHECK(addV1.at(1) == Approx(5.3 + 6.3));
		CHECK(addV1.at(2) == Approx(5.3 + 6.3));

		addV1 = ev2 + zeroV;
		CHECK(addV1.dimensions() == 3);
		CHECK(addV1.at(0) == Approx(6.3));
		CHECK(addV1.at(1) == Approx(6.3));
		CHECK(addV1.at(2) == Approx(6.3));
		CHECK(addV1 == ev2);

		auto ev3 = comp6771::euclidean_vector(5, 3.3);

		CHECK_THROWS_WITH(addV1 = ev2 + ev3, "Dimensions of LHS(3) and RHS(5) do not match");
	}

	SECTION("Subtraction") {
		auto ev1 = comp6771::euclidean_vector(3, 5.3);
		auto const ev2 = comp6771::euclidean_vector{6.3, 6.3, 6.3};
		auto zeroV = comp6771::euclidean_vector(3, 0.0);

		auto subV1 = ev1 - ev2;
		CHECK(subV1.dimensions() == 3);
		CHECK(subV1.at(0) == Approx(5.3 - 6.3));
		CHECK(subV1.at(1) == Approx(5.3 - 6.3));
		CHECK(subV1.at(2) == Approx(5.3 - 6.3));

		subV1 = ev2 - zeroV;
		CHECK(subV1.dimensions() == 3);
		CHECK(subV1.at(0) == Approx(6.3));
		CHECK(subV1.at(1) == Approx(6.3));
		CHECK(subV1.at(2) == Approx(6.3));
		CHECK(subV1 == ev2);

		auto ev3 = comp6771::euclidean_vector(5, 3.3);

		CHECK_THROWS_WITH(subV1 = ev2 - ev3, "Dimensions of LHS(3) and RHS(5) do not match");
	}

	SECTION("Multiply") {
		auto ev1 = comp6771::euclidean_vector(3, 3.0);
		auto ev2 = comp6771::euclidean_vector{4.0, 4.0, 4.0, 4.0};

		ev1 = ev2 * 3;
		ev2 = 4 * ev1;
		CHECK(ev1.dimensions() == ev2.dimensions());
		CHECK(ev1.at(0) == Approx(12.0));
		CHECK(ev1.at(1) == Approx(12.0));
		CHECK(ev1.at(2) == Approx(12.0));

		CHECK(ev2.at(0) == Approx(48.0));
		CHECK(ev2.at(1) == Approx(48.0));
		CHECK(ev2.at(2) == Approx(48.0));

		ev1 = ev2 * 0;
		ev2 = 0 * ev1;
		CHECK(ev1 == ev2);
	}

	SECTION("Divide") {
		auto ev1 = comp6771::euclidean_vector(3, 12.0);
		auto ev2 = comp6771::euclidean_vector{12.0, 12.0, 12.0, 12.0};

		ev1 = ev2 / 2.0;
		CHECK(ev1.dimensions() == ev2.dimensions());
		CHECK(ev1.at(0) == Approx(6.0));
		CHECK(ev1.at(1) == Approx(6.0));
		CHECK(ev1.at(2) == Approx(6.0));

		ev2 = ev1 / 2.0;
		CHECK(ev2.at(0) == Approx(3.0));
		CHECK(ev2.at(1) == Approx(3.0));
		CHECK(ev2.at(2) == Approx(3.0));

		CHECK_THROWS_WITH(ev1 = ev2 / 0, "Invalid vector division by 0");
	}

	SECTION("Output Stream") {
		auto const ev1 = comp6771::euclidean_vector(5, 3.0);
		auto ev2 = comp6771::euclidean_vector(5, 3.0);
		auto ev3 = comp6771::euclidean_vector{1.0, 2.0, 3.0, 4.5, 5.5};

		auto oss1 = std::ostringstream{};
		oss1 << (ev1 + ev2 + ev3);
		CHECK(oss1.str() == "[7 8 9 10.5 11.5]");

		auto ev4 = comp6771::euclidean_vector(0, 0.0);
		auto oss2 = std::ostringstream{};
		oss2 << (ev4);
		CHECK(oss2.str() == "[]");

		auto ev5 = comp6771::euclidean_vector(1, 5.5);
		auto oss3 = std::ostringstream{};
		oss3 << (ev5);
		CHECK(oss3.str() == "[5.5]");
	}
}