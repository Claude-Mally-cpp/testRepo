#include <hobby/hobbyMath.h>

namespace hobby {

std::vector<uint64_t> getDivisors(uint64_t n) {
    std::vector<uint64_t> divisors;

    // Iterate from 1 to the square root of the absolute value of n
    for (uint64_t i = 1; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {  // If i is a divisor
            divisors.push_back(i);
            if (i != n / i) {  // If abs_n / i is a different divisor
                divisors.push_back(n / i);
            }
        }
    }
    std::sort(divisors.begin(), divisors.end());
    return divisors;
}

size_t getDivisorsCount(uint64_t n) {
    size_t count = 0;
    // Iterate from 1 to the square root of the absolute value of n
    for (uint64_t i = 1; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {  // If i is a divisor
            count++;
            if (i != n / i) {  // If abs_n / i is a different divisor
                count++;
            }
        }
    }
    return count;
}

}  // namespace hobby