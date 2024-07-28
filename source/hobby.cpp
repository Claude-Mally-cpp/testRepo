#include <hobby/hobby.h>
#include <hobby/hobbyMath.h>

/// @todo put this hack in a seperate header file
#ifdef _MSC_VER  // Check if the compiler is MSVC (Windows)
#  pragma warning(push)
#  pragma warning(disable : 4459)
#endif

#include <fmt/format.h>

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

using namespace hobby;

Hobby::Hobby(std::string _name) : name(std::move(_name)) {}

std::string Hobby::greet(LanguageCode lang) const {
  switch (lang) {
    default:
    case LanguageCode::EN:
      return fmt::format("Hello, {}!", name);
    case LanguageCode::DE:
      return fmt::format("Hallo {}!", name);
    case LanguageCode::ES:
      return fmt::format("¡Hola {}!", name);
    case LanguageCode::FR:
      return fmt::format("Bonjour {}!", name);
  }
}
