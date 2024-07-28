#pragma once

#include <numeric>

namespace hobby {

  // Base case for recursion, returns the GCD of two integers
  template <typename T> constexpr T gcd(T a, T b) { return std::gcd(a, b); }

  /// @brief variadic template to calculate greatest common denominator
  template <typename T, typename... Args> constexpr T gcd(T first, Args... args) {
    return gcd(first, gcd(args...));
  }

  static_assert(gcd(6, -6, 10, -10) == 2);
  static_assert(gcd(24, -24, 0) == 24);

  // Base case for recursion, returns the lcm of two integers
  template <typename T> constexpr T lcm(T a, T b) { return std::lcm(a, b); }

  /// @brief variadic template to calculate the least common multiple for multiple integers
  template <typename T, typename... Args> constexpr T lcm(T first, Args... args) {
    return lcm(first, lcm(args...));
  }

  constexpr int p{2 * 2 * 3};
  constexpr int q{2 * 3 * 3};
  static_assert(2 * 2 * 3 * 3 == lcm(p, q));
  static_assert(225 == lcm(45, 75));

  static_assert(lcm(6, -6, 10, -10) == 30);
  static_assert(lcm(6, -10) == 30);
  static_assert(lcm(-6, -10) == 30);
  static_assert(lcm(24, -24, 0) == 0);
};  // namespace hobby