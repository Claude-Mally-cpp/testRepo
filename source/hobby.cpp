#include <hobby/hobby.hpp>

using namespace hobby;

Hobby::Hobby(std::string _name) : name(std::move(_name)) {}

auto Hobby::greet(LanguageCode lang) const -> std::string {
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
