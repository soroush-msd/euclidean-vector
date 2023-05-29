// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <list>
#include <numeric>
#include <string>
#include <vector>

namespace comp6771 {

	// Implement solution here

	// Defualt Constructor - delegated
	euclidean_vector::euclidean_vector() noexcept
	: euclidean_vector::euclidean_vector(1, 0.0) {}

	// Single-argument Constructor - delegated
	euclidean_vector::euclidean_vector(int dimension) noexcept
	: euclidean_vector::euclidean_vector(dimension, 0.0) {}

	// Constrcutor - taking the number of dimensions and magnitude in each dimension
	euclidean_vector::euclidean_vector(int dimension, double magnitude) noexcept
	: dimension_{static_cast<std::size_t>(dimension)}
	, magnitude_{std::make_unique<double[]>(dimension_)} {
		std::fill(magnitude_.get(), magnitude_.get() + dimension_, magnitude);
	}

	// Constructor - taking the bginning and the end iterators of a vector of type <double>
	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
	                                   std::vector<double>::const_iterator end) noexcept
	: dimension_{static_cast<std::size_t>(std::distance(start, end))}
	, magnitude_{std::make_unique<double[]>(dimension_)} {
		std::copy(start, end, magnitude_.get());
	}

	// Constructor - taking an initliase list of doubles
	euclidean_vector::euclidean_vector(std::initializer_list<double> init_list) noexcept
	: dimension_{static_cast<std::size_t>(init_list.size())}
	, magnitude_{std::make_unique<double[]>(dimension_)} {
		std::copy(init_list.begin(), init_list.end(), magnitude_.get());
	}

	// Copy Constrcutor
	euclidean_vector::euclidean_vector(euclidean_vector const& old) noexcept
	: dimension_{old.dimension_}
	, magnitude_{std::make_unique<double[]>(dimension_)} {
		std::copy(old.magnitude_.get(), old.magnitude_.get() + dimension_, magnitude_.get());
	}

	// Move Constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& old) noexcept
	: dimension_{old.dimension_}
	, magnitude_{std::move(old.magnitude_)} {
		old.dimension_ = 0;
	}

	// Operations

	// Copy Assignment
	auto euclidean_vector::operator=(euclidean_vector const& old) noexcept -> euclidean_vector& {
		dimension_ = old.dimension_;
		magnitude_ = std::make_unique<double[]>(dimension_);
		std::copy(old.magnitude_.get(), old.magnitude_.get() + dimension_, magnitude_.get());
		return *this;
	}

	// Move Assignment
	auto euclidean_vector::operator=(euclidean_vector&& old) noexcept -> euclidean_vector& {
		dimension_ = old.dimension_;
		magnitude_ = std::make_unique<double[]>(dimension_);
		magnitude_ = std::move(old.magnitude_);
		old.dimension_ = 0;
		return *this;
	}

	// Subscript - non-const definition
	auto euclidean_vector::operator[](int index) noexcept -> double& {
		assert(index >= 0 && static_cast<std::size_t>(index) < dimension_);
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return this->magnitude_[static_cast<std::size_t>(index)];
	}

	// Subscript - const definition
	auto euclidean_vector::operator[](int index) const noexcept -> const double& {
		assert(index >= 0 && static_cast<std::size_t>(index) < dimension_);
		return this->magnitude_[static_cast<std::size_t>(index)];
	}

	// Unary Plus
	auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
		return euclidean_vector(*this);
	}

	// Negation
	auto euclidean_vector::operator-() const noexcept -> euclidean_vector {
		auto negation = euclidean_vector(*this);
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               negation.magnitude_.get(),
		               std::negate<>{});
		return negation;
	}

	// Compound Addition
	auto euclidean_vector::operator+=(euclidean_vector const& add_vector) -> euclidean_vector& {
		if (dimension_ != add_vector.dimension_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(dimension_) + ") and RHS("
			                             + std::to_string(add_vector.dimension_) + ") do not match");
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               add_vector.magnitude_.get(),
		               magnitude_.get(),
		               std::plus<>{});
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return *this;
	}

	// Compound Subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& add_vector) -> euclidean_vector& {
		if (dimension_ != add_vector.dimension_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(dimension_) + ") and RHS("
			                             + std::to_string(add_vector.dimension_) + ") do not match");
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               add_vector.magnitude_.get(),
		               magnitude_.get(),
		               std::minus<>{});
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return *this;
	}

	// Compound Multiplication
	auto euclidean_vector::operator*=(double multiplier) noexcept -> euclidean_vector& {
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               [&multiplier](double& elem) { return (elem * multiplier); });
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return *this;
	}

	// Compound Division
	auto euclidean_vector::operator/=(double divider) -> euclidean_vector& {
		if (divider == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               [&divider](double& elem) { return (elem / divider); });
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return *this;
	}

	// Vector Type Conversion
	euclidean_vector::operator std::vector<double>() const noexcept {
		auto vector_type = std::vector<double>(dimension_);
		std::copy(magnitude_.get(), magnitude_.get() + dimension_, vector_type.begin());
		return vector_type;
	}

	// List Type Conversion
	euclidean_vector::operator std::list<double>() const noexcept {
		auto list_type = std::list<double>(dimension_);
		std::copy(magnitude_.get(), magnitude_.get() + dimension_, list_type.begin());
		return list_type;
	}

	// Member Functions

	// at - const definition
	auto euclidean_vector::at(int index) const -> double {
		if (index < 0 || static_cast<std::size_t>(index) >= dimension_) {
			throw euclidean_vector_error("Index " + std::to_string(index)
			                             + " is not valid for this euclidean_vector object");
		}
		return this->magnitude_[static_cast<std::size_t>(index)];
	}

	// at - non-const definition
	auto euclidean_vector::at(int index) -> double& {
		if (index < 0 || static_cast<std::size_t>(index) >= dimension_) {
			throw euclidean_vector_error("Index " + std::to_string(index)
			                             + " is not valid for this euclidean_vector object");
		}
		if (cache_status_ == true) {
			cache_status_ = false;
		}
		return this->magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::dimensions() const noexcept -> int {
		return static_cast<int>(this->dimension_);
	}

	// getter to get the value of the stored norm
	auto euclidean_vector::get_cache() const -> double {
		return cache_value_;
	}

	// setter to set the new value of the norm
	auto euclidean_vector::set_cache(double new_cache) const -> void {
		cache_status_ = true;
		cache_value_ = new_cache;
	}

	// Utility Functions

	auto euclidean_norm(euclidean_vector const& v) noexcept -> double {
		if (v.dimensions() == 0) {
			return 0.0;
		}
		if (v.cache_status_) {
			return v.get_cache();
		}
		auto norm = std::sqrt(std::inner_product(v.magnitude_.get(),
		                                         v.magnitude_.get() + v.dimension_,
		                                         v.magnitude_.get(),
		                                         0.0));
		v.set_cache(norm);
		return norm;
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		if (euclidean_norm(v) == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		auto norm_val = euclidean_norm(v);
		return (v / norm_val);
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimensions())
			                             + ") and RHS(" + std::to_string(y.dimensions())
			                             + ") do not match");
		}
		auto dot_value = std::inner_product(&x[0], &x[0] + x.dimensions(), &y[0], 0.0);
		return dot_value;
	}

} // namespace comp6771
