#pragma once

#include <cmath>
#include <concepts>
#include <cstdlib>  // For std::abs
#include <string>
#include <vector>

namespace hobby {

    /**  Language codes to be used with the Hobby class */
    enum class LanguageCode { EN, DE, ES, FR };

    /**
     * @brief A class for saying hello in multiple languages
     */
    class Hobby {
        std::string name;

      public:
        /**
         * @brief Creates a new hobby
         * @param name the name to greet
         */
        Hobby(std::string name);

        /**
         * @brief Creates a localized string containing the greeting
         * @param lang the language to greet in
         * @return a string containing the greeting
         */
        std::string greet(LanguageCode lang = LanguageCode::EN) const;
    };

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

        return divisors;
    }

}  // namespace hobby
