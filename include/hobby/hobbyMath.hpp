#pragma once

#include <stdint.h>

#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <hobby/hobby.hpp>
#include <numeric>
#include <vector>

namespace hobby {

/// @brief Computes the greatest common divisor (GCD) of two integral values.
/// @tparam T A type that must satisfy the Integral concept (e.g., int, long).
/// @param a The first integral value.
/// @param b The second integral value.
/// @returns The greatest common divisor of the two integral values.
///
/// This function serves as the base case for the recursive variadic template.
/// It relies on `std::gcd` to compute the GCD of two values.
///
/// Example usage:
/// @code
/// int result = gcd(12, 18); // result will be 6
/// @endcode
template <typename T>
constexpr T gcd(T a, T b) {
    return std::gcd(a, b);
}
static_assert(gcd(12, 18) == 6);

/// @brief Computes the greatest common divisor (GCD) for multiple integral
/// values.
/// @tparam T A type that must satisfy the Integral concept (e.g., int, long).
/// @tparam Args Variadic template parameter pack, representing additional
/// integral values.
/// @param first The first integral value.
/// @param args Additional integral values.
/// @returns The greatest common divisor of all the provided integral values.
///
/// This function computes the GCD of multiple values by recursively applying
/// the GCD calculation to the first element and the GCD of the remaining
/// values.
///
/// Example usage:
/// @code
/// int result = gcd(12, 18, 24); // result will be 6
/// @endcode
template <typename T, typename... Args>
constexpr T gcd(T first, Args... args) {
    return gcd(first, gcd(args...));
}
static_assert(gcd(12, 18, 24) == 6);
static_assert(gcd(6, -6, 10, -10) == 2);
static_assert(gcd(24, -24, 0) == 24);

/// @brief Computes the least common multiple (LCM) of two integral values.
/// @tparam T A type that must satisfy the Integral concept (e.g., int, long).
/// @param a The first integral value.
/// @param b The second integral value.
/// @returns The least common multiple of the two integral values.
///
/// This function serves as the base case for the recursive variadic template.
/// It relies on `std::lcm` to compute the LCM of two values.
///
/// Example usage:
/// @code
/// int result = lcm(4, 5); // result will be 20
/// @endcode
template <typename T>
constexpr T lcm(T a, T b) {
    return std::lcm(a, b);
}
static_assert(lcm(4, 5) == 20);

/// @brief Computes the least common multiple (LCM) for multiple integral
/// values.
/// @tparam T A type that must satisfy the Integral concept (e.g., int, long).
/// @tparam Args Variadic template parameter pack, representing additional
/// integral values.
/// @param first The first integral value.
/// @param args Additional integral values.
/// @returns The least common multiple of all the provided integral values.
///
/// This function computes the LCM of multiple values by recursively applying
/// the LCM calculation to the first element and the LCM of the remaining
/// values.
///
/// Example usage:
/// @code
/// int result = lcm(4, 5, 6); // result will be 60
/// @endcode
template <typename T, typename... Args>
constexpr T lcm(T first, Args... args) {
    return lcm(first, lcm(args...));
}
static_assert(lcm(4, 5, 6) == 60);

constexpr int p{2 * 2 * 3};
constexpr int q{2 * 3 * 3};
static_assert(2 * 2 * 3 * 3 == lcm(p, q));
static_assert(225 == lcm(45, 75));

static_assert(lcm(6, -6, 10, -10) == 30);
static_assert(lcm(6, -10) == 30);
static_assert(lcm(-6, -10) == 30);
static_assert(lcm(24, -24, 0) == 0);

// Concept to ensure the type is an integral type
template <typename T>
concept Integral = std::is_integral_v<T>;

/// @brief Function to find all divisors of a given number
/// @param number for divisor gathering
std::vector<uint64_t> getDivisors(uint64_t number);

/// @brief get the number of divisors for given number
/// @param number for divisor counting
/// @return total number of divisors. if less than 3 then the number is prime
size_t getDivisorsCount(uint64_t number);

constexpr bool isPrime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;  // 2 and 3 are prime

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

constexpr uint64_t nextPrime(uint64_t n) {
    n++;
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

};  // namespace hobby