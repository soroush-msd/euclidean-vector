#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Declaring constructors
		euclidean_vector() noexcept;
		explicit euclidean_vector(int dimension) noexcept;
		euclidean_vector(int dimension, double magnitude) noexcept;
		euclidean_vector(std::vector<double>::const_iterator start,
		                 std::vector<double>::const_iterator end) noexcept;
		euclidean_vector(std::initializer_list<double> init_list) noexcept;
		euclidean_vector(euclidean_vector const& old) noexcept;
		euclidean_vector(euclidean_vector&& old) noexcept;

		// Decalring the destrcutor
		~euclidean_vector() noexcept = default;

		// Declaring Operations
		auto operator=(euclidean_vector const& old) noexcept -> euclidean_vector&;
		auto operator=(euclidean_vector&& old) noexcept -> euclidean_vector&;
		auto operator[](int index) noexcept -> double&;
		auto operator[](int index) const noexcept -> const double&;
		auto operator+() const noexcept -> euclidean_vector;
		auto operator-() const noexcept -> euclidean_vector;
		auto operator+=(euclidean_vector const& add_vector) -> euclidean_vector&;
		auto operator-=(euclidean_vector const& add_vector) -> euclidean_vector&;
		auto operator*=(double multiplier) noexcept -> euclidean_vector&;
		auto operator/=(double divider) -> euclidean_vector&;

		// Declaring Conversion Types
		explicit operator std::vector<double>() const noexcept;
		explicit operator std::list<double>() const noexcept;

		// Declaring Member Functions
		auto at(int index) const -> double;
		auto at(int index) -> double&;
		auto dimensions() const noexcept -> int;

		// Defining Friends

		// Equal Operator
		friend auto
		operator==(euclidean_vector const& vector1, euclidean_vector const& vector2) noexcept -> bool {
			if (vector1.dimension_ == vector2.dimension_) {
				if (std::equal(vector1.magnitude_.get(),
				               vector1.magnitude_.get() + vector1.dimension_,
				               vector2.magnitude_.get(),
				               vector2.magnitude_.get() + vector2.dimension_))
				{
					return true;
				}
			}
			return false;
		}

		// Not Equal Operator
		friend auto
		operator!=(euclidean_vector const& vector1, euclidean_vector const& vector2) noexcept -> bool {
			return !(vector1 == vector2);
		}

		// Addition
		friend auto operator+(euclidean_vector const& vector1, euclidean_vector const& vector2)
		   -> euclidean_vector {
			if (vector1.dimension_ != vector2.dimension_) {
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(vector1.dimension_)
				                             + ") and RHS(" + std::to_string(vector2.dimension_)
				                             + ") do not match");
			}
			auto vector_result = euclidean_vector(vector1.dimensions());
			std::transform(vector1.magnitude_.get(),
			               vector1.magnitude_.get() + vector1.dimension_,
			               vector2.magnitude_.get(),
			               vector_result.magnitude_.get(),
			               std::plus<>{});
			return vector_result;
		}

		// Subtraction
		friend auto operator-(euclidean_vector const& vector1, euclidean_vector const& vector2)
		   -> euclidean_vector {
			if (vector1.dimension_ != vector2.dimension_) {
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(vector1.dimension_)
				                             + ") and RHS(" + std::to_string(vector2.dimension_)
				                             + ") do not match");
			}

			auto vector_result = euclidean_vector(vector1.dimensions());
			std::transform(vector1.magnitude_.get(),
			               vector1.magnitude_.get() + vector1.dimension_,
			               vector2.magnitude_.get(),
			               vector_result.magnitude_.get(),
			               std::minus<>{});
			return vector_result;
		}

		// Multiply -> vector * scalar
		friend auto operator*(euclidean_vector const& vector, double multiplier) noexcept
		   -> euclidean_vector {
			auto vector_result = euclidean_vector(vector.dimensions());
			std::transform(vector.magnitude_.get(),
			               vector.magnitude_.get() + vector.dimension_,
			               vector_result.magnitude_.get(),
			               [&multiplier](double& elem) { return (elem * multiplier); });
			return vector_result;
		}

		// Multiply -> scalar * vector
		friend auto operator*(double multiplier, euclidean_vector const& vector) noexcept
		   -> euclidean_vector {
			return (vector * multiplier);
		}

		// Divide
		friend auto operator/(euclidean_vector const& vector, double divider) -> euclidean_vector {
			if (divider == 0) {
				throw euclidean_vector_error("Invalid vector division by 0");
			}
			auto vector_result = euclidean_vector(vector.dimensions());
			std::transform(vector.magnitude_.get(),
			               vector.magnitude_.get() + vector.dimension_,
			               vector_result.magnitude_.get(),
			               [&divider](double& elem) { return (elem / divider); });
			return vector_result;
		}

		// Output Stream
		friend auto operator<<(std::ostream& os, euclidean_vector const& vector) noexcept
		   -> std::ostream& {
			if (vector.dimension_ == 0) {
				os << "[]";
				return os;
			}
			os << "[";
			std::copy(vector.magnitude_.get(),
			          vector.magnitude_.get() + vector.dimension_ - 1,
			          std::ostream_iterator<double>(os, " "));
			std::copy(vector.magnitude_.get() + vector.dimension_ - 1,
			          vector.magnitude_.get() + vector.dimension_,
			          std::ostream_iterator<double>(os));
			os << "]";
			return os;
		}

	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::size_t dimension_;
		std::unique_ptr<double[]> magnitude_;
		mutable bool cache_status_ = false;
		mutable double cache_value_ = 0.0;
		auto get_cache() const -> double;
		auto set_cache(double new_cache) const -> void;

		// norm - non-hidden friend
		friend auto euclidean_norm(euclidean_vector const& v) noexcept -> double;
	};

	// norm - non-hidden friend
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double;

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
