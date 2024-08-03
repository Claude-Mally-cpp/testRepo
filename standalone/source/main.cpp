#include <fmt/format.h>
#include <fmt/ranges.h>
#include <hobby/hobby.h>
#include <hobby/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
    const std::unordered_map<std::string, hobby::LanguageCode> languages{
        {"en", hobby::LanguageCode::EN},
        {"de", hobby::LanguageCode::DE},
        {"es", hobby::LanguageCode::ES},
        {"fr", hobby::LanguageCode::FR},
    };

    cxxopts::Options options(*argv, "A program to welcome the world!");

    std::string language;
    std::string name;

    // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        fmt::println("{}", options.help());
        return 0;
    }

    if (result["version"].as<bool>()) {
        fmt::println("Hobby, version {}", HOBBY_VERSION);
        return 0;
    }

    auto langIt = languages.find(language);
    if (langIt == languages.end()) {
        fmt::println(stderr, "unknown language code: \"{}\"", language);
        return 1;
    }

    hobby::Hobby hobby(name);
    const auto message = hobby.greet(langIt->second);
    fmt::println("{}", message);
    fmt::println("{}", hobby.greet(langIt->second));

    const auto number = 144;

    std::vector<int> divisors = hobby::getDivisors(number);
    fmt::println("Divisors of {} are [{}]", number, fmt::join(divisors, ", "));
    return 0;
}
