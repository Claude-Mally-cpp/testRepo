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

    // Concept to ensure the type is an integral type
    template <typename T>
    concept Integral = std::is_integral_v<T>;

    // Function to find all divisors of a given integer
    template <Integral T> std::vector<T> getDivisors(T n) {
        std::vector<T> divisors;
        T abs_n = std::abs(n);  // Take the absolute value of n

        // Iterate from 1 to the square root of the absolute value of n
        for (T i = 1; i <= std::sqrt(abs_n); ++i) {
            if (abs_n % i == 0) {  // If i is a divisor
                divisors.push_back(i);
                if (i != abs_n / i) {  // If abs_n / i is a different divisor
                    divisors.push_back(abs_n / i);
                }
            }
        }

        // If the original number was negative, also add the negative divisors
        if (n < 0) {
            size_t size = divisors.size();
            for (size_t i = 0; i < size; ++i) {
                divisors.push_back(-divisors[i]);
            }
        }

        std::sort(divisors.begin(), divisors.end());
        return divisors;
    }

};  // namespace hobby