#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// <<Test Rationale>>
// In this test file, we will test different constructors,
// to ensure the objects can be validly created.
// Therefore, dimensions and elements of each object
// is compared with their expected values according to the specification to
// aviod unnecessary reliance on other functions.
// The tests are designed in a way to make sure that different scenarios
// and different edge cases are covered by inputting different values
// to test different functions and different possible paths.
// To address this, we start by simplest functions of the implementation
// and move forward. This way we make sure that functions with less prerequisites
// are tested fisrt before moving to things with more prerequisites.
// In this way, I made sure that the implementation works as it is
// supposed to.

// for testing constructors, I tried to minimise the amount of reliance on other
// functions implemented. for the few first iterators, I constructed smaller objects
// and tested them with dimensions() and at() for each element.
// for the few last constructors, I created larger objects and created another one
// through previously tested constructors and then compared the two objects
// through == operator as ==operator has a simple and robust
// implementation. So I was able to make my tests more minimal.

TEST_CASE("Part 1. Constructors") {
	// In this section, we test default constructors.
	// According to the spec, they need to have the dimension of size 1 with the magnitude 0.0
	SECTION("Default Constrcutor") {
		auto ev1 = comp6771::euclidean_vector();
		CHECK(ev1.dimensions() == 1);
		CHECK(ev1.at(0) == Approx(0.0));

		auto ev2 = comp6771::euclidean_vector();
		CHECK(ev2.dimensions() == 1);
		CHECK(ev2.at(0) == Approx(0.0));
	}

	// In this section, we test single-argument constructors.
	// They take in an integer to create an object of the size of that integer
	// with the magnitude of 0.0 for each dimension.
	SECTION("Single-argument constructor") {
		auto ev1 = comp6771::euclidean_vector(1);
		CHECK(ev1.dimensions() == 1);
		CHECK(ev1.at(0) == Approx(0.0));

		int i{3};
		auto ev2 = comp6771::euclidean_vector(i);
		CHECK(ev2.dimensions() == 3);
		CHECK(ev2.at(0) == Approx(0.0));
		CHECK(ev2.at(1) == Approx(0.0));
		CHECK(ev2.at(2) == Approx(0.0));

		auto ev3 = comp6771::euclidean_vector(0);
		CHECK(ev3.dimensions() == 0);
	}

	// A constructor that takes the number of dimensions (as an int) and initialises the
	// magnitude in each dimension as the second argument (a double).
	SECTION("euclidean_vector(int, double)") {
		auto ev1 = comp6771::euclidean_vector(2, 4.0);
		CHECK(ev1.dimensions() == 2);
		CHECK(ev1.at(0) == Approx(4.0));
		CHECK(ev1.at(1) == Approx(4.0));

		auto x = int{3};
		auto y = double{3.24};
		auto ev2 = comp6771::euclidean_vector(x, y);
		CHECK(ev2.dimensions() == 3);
		CHECK(ev2.at(0) == Approx(3.24));
		CHECK(ev2.at(1) == Approx(3.24));
		CHECK(ev2.at(2) == Approx(3.24));

		auto ev3 = comp6771::euclidean_vector(0, 4.4);
		CHECK(ev3.dimensions() == 0);
	}

	SECTION("Const_iterator constructor") {
		std::vector<double> v1;
		auto ev1 = comp6771::euclidean_vector(v1.begin(), v1.end());
		CHECK(ev1.dimensions() == 0);

		std::vector<double> v2{1.1, 2.2, 3.3};
		auto ev2 = comp6771::euclidean_vector(v2.begin(), v2.end());
		CHECK(ev2.dimensions() == 3);
		CHECK(ev2.at(0) == Approx(1.1));
		CHECK(ev2.at(1) == Approx(2.2));
		CHECK(ev2.at(2) == Approx(3.3));
	}

	SECTION("Initializer_list constructor") {
		auto v = std::vector<double>{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};
		auto ev1 = comp6771::euclidean_vector(v.begin(), v.end());
		auto ev2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 0.1322, 4.23432, 2112.3, 64.2123};

		CHECK(ev1.dimensions() == 8);
		CHECK(ev2.dimensions() == 8);
		CHECK(ev1 == ev2);
	}

	SECTION("Copy Constructor") {
		auto ev1 = comp6771::euclidean_vector{1.0213, 2.56, 3, 4.1, 0.1322, 4.23432, 2112.3, 64.2123};
		auto copy = comp6771::euclidean_vector(ev1);

		CHECK(ev1.dimensions() == 8);
		CHECK(copy.dimensions() == 8);
		CHECK(ev1 == copy);
	}

	SECTION("Move Constructor") {
		auto ev1 = comp6771::euclidean_vector{1.0213, 2.56, 3, 4.1, 0.1322, 4.23432, 2112.3, 64.2123};
		auto ev2 = comp6771::euclidean_vector{1.0213, 2.56, 3, 4.1, 0.1322, 4.23432, 2112.3, 64.2123};
		auto move = comp6771::euclidean_vector(std::move(ev1));

		CHECK(ev1.dimensions() == 0);
		CHECK(move.dimensions() == 8);
		CHECK(move == ev2);
	}
}
