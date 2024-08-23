#include "hobby.h"

#include <doctest/doctest.h>
#include <hobby/version.h>

#include <array>
#include <string>

#include "hobbyMath.h"

TEST_CASE("Hobby") {
    using namespace hobby;

    Hobby hobby("Tests");

    CHECK(hobby.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(hobby.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(hobby.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(hobby.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Divisors") {
    const auto value = 360;
    const auto expectedDivisors = std::vector<uint64_t>{
        1,  2,  3,  4,  5,  6,  8,  9,  10, 12,  15,  18,
        20, 24, 30, 36, 40, 45, 60, 72, 90, 120, 180, 360};
    const auto divisorsVector = hobby::getDivisors(value);
    CHECK(expectedDivisors == divisorsVector);
}

TEST_CASE("Prime number detector") {
    constexpr std::array primes = {
        // Subset of small primes
        2ULL, 11ULL, 17ULL, 29ULL, 41ULL, 59ULL, 73ULL, 89ULL, 113ULL, 137ULL,
        149ULL, 167ULL, 181ULL, 197ULL, 211ULL, 229ULL, 251ULL, 269ULL, 293ULL,
        317ULL, 337ULL, 359ULL, 373ULL, 389ULL, 409ULL,

        // Primes in the uint16_t range, avoiding values that are close together
        1031ULL, 1103ULL, 1223ULL, 1361ULL, 1489ULL, 1607ULL, 1741ULL, 1873ULL,
        2011ULL, 2141ULL, 2267ULL, 2389ULL, 2531ULL, 2657ULL, 2791ULL, 2927ULL,
        3079ULL, 3209ULL, 3347ULL, 3491ULL, 3637ULL, 3767ULL, 3911ULL, 4049ULL,
        4211ULL,

        // Primes in the uint32_t & uint64_t range, avoiding values that are
        // close together
        104729ULL, 130379ULL, 160481ULL, 456979ULL, 832919ULL, 1827337ULL,
        3267697ULL, 3653081ULL, 4294967311ULL, 12884901947ULL, 38654705849ULL,
        115964117579ULL, 347892352757ULL, 1043677058297ULL, 3131031174907ULL,
        9393093524767ULL, 28179280574353ULL, 84537841723211ULL,
        84537841723217ULL, 253613525169689ULL, 760840575509089ULL,
        2282521726527281ULL, 6847565179581859ULL, 20542695538745609ULL,
        61628086616236837ULL, 184884259848710551ULL, 554652779546131709ULL,
        1663958338638395171ULL};

    for (auto current : primes) {
        // CHECK_MESSAGE(hobby::isPrime(current), "Failed for value: ",
        // current);
        CHECK(hobby::isPrime(current));
        if (current > 2) {
            CHECK(!hobby::isPrime(current + 1));
        }
    }
}
