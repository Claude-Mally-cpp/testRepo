#include <fmt/format.h>
#include <fmt/ranges.h>
#include <hobby/hobby.h>
#include <hobby/hobbyMath.h>
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
    ("d,divisor", "show divisors", cxxopts::value<int64_t>())
    ("p,prime", "test if prime", cxxopts::value<int64_t>())
    ("g,generate", "generate an array of 10 primes higher that argument", cxxopts::value<uint64_t>())
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

    if (result.count("divisor")) {
        const auto value = result["divisor"].as<int64_t>();
        const auto divisors = hobby::getDivisors(value);
        fmt::println("Divisors of {} are {{{}}}", value,
                     fmt::join(divisors, ", "));
    }
    if (result.count("prime")) {
        const auto value = result["prime"].as<int64_t>();
        const auto isPrime = hobby::isPrime(value);
        fmt::println("number {} isPrime={}", value, isPrime);
    }
    if (result.count("generate")) {
        auto value = result["generate"].as<uint64_t>();
        for (size_t index = 0; index < 10; index++) {
            value = hobby::nextPrime(value);
            const auto divisors = hobby::getDivisors(value);
            assert(divisors.size()==2);
            fmt::print("{}, ", value);
            value *= 3;
        }
        fmt::print("\n");
    }
    return 0;
}
