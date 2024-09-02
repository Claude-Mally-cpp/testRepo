#include <doctest/doctest.h>
#include <hobby/version.h>

#include <array>
#include <hobby/hobby.hpp>
#include <hobby/hobbyDice.hpp>
#include <hobby/hobbyMath.hpp>
#include <string>

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

using hobby::dice;

TEST_CASE("Testing valid dice creation and rolling") {
    // Create a dice with 6 sides, default type uint32_t
    dice<> d6(6);
    CHECK(d6.getSides() == 6);

    // Roll the dice multiple times and check the results are within the valid
    // range
    for (int i = 0; i < 100; ++i) {
        uint32_t result = d6.roll();
        CHECK(result >= 1);
        CHECK(result <= 6);
    }

    // Create a dice with 20 sides, using uint16_t as the type
    dice<uint16_t> d20(20);
    CHECK(d20.getSides() == 20);

    // Roll the dice multiple times and check the results are within the valid
    // range
    for (int i = 0; i < 100; ++i) {
        uint16_t result = d20.roll();
        CHECK(result >= 1);
        CHECK(result <= 20);
    }
}

TEST_CASE("Testing invalid dice creation") {
    // Attempt to create a dice with 0 sides and expect an exception
    CHECK_THROWS_AS(dice<>(0), std::invalid_argument);
}

TEST_CASE("Testing type consistency") {
    // Create a dice with 10 sides, using uint16_t as the type
    dice<uint16_t> d10(10);

    // Check that roll() returns a value of type uint16_t
    auto rollResult = d10.roll();
    CHECK(std::is_same<decltype(rollResult), uint16_t>::value);

    // Check that getSides() returns a value of type uint16_t
    auto sidesResult = d10.getSides();
    CHECK(std::is_same<decltype(sidesResult), uint16_t>::value);
}
