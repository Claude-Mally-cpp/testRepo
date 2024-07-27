#include <doctest/doctest.h>
#include <hobby/hobby.h>
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

TEST_CASE("Hobby version") {
  static_assert(std::string_view(HOBBY_VERSION) == std::string_view("1.0"));
  CHECK(std::string(HOBBY_VERSION) == std::string("1.0"));
}
