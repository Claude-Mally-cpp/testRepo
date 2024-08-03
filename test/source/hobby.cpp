#include <doctest/doctest.h>
#include <hobby/hobby.h>
#include <hobby/hobbyMath.h>
#include <hobby/version.h>

#include <string>

TEST_CASE("Hobby") {
    using namespace hobby;

    Hobby hobby("Tests");

    CHECK(hobby.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(hobby.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(hobby.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(hobby.greet(LanguageCode::FR) == "Bonjour Tests!");
}

// TEST_CASE("Hobby version") {
//     static_assert(std::string_view(HOBBY_VERSION) == std::string_view("1.0"));
//     CHECK(std::string(HOBBY_VERSION) == std::string("1.0"));
// }

TEST_CASE("Divisors") {
    const auto value = 360;
    const auto expectedDivisors = std::vector{1,  2,  3,  4,  5,  6,  8,  9,  10, 12,  15,  18,
                                              20, 24, 30, 36, 40, 45, 60, 72, 90, 120, 180, 360};
    const auto divisorsVector = hobby::getDivisors(value);
    CHECK(expectedDivisors == divisorsVector);
}
