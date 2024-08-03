#include <hobby/hobby.h>
#include <hobby/version.h>

#include <fmt/format.h>
#include <hobby/hobby.h>
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
    fmt::print("{}\n", options.help());
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Hobby, version " << HOBBY_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  hobby::Hobby hobby(name);
  const auto message =  hobby.greet(langIt->second);
  fmt::print("{}\n", message);
  std::cout << hobby.greet(langIt->second) << std::endl;

  int number = 144;

  std::vector<int> divisors = hobby::getDivisors(number);
  std::cout << "Divisors of " << number << " are: ";
  for (int divisor : divisors) {
    std::cout << divisor << " ";
  }
  std::cout << std::endl;

  return 0;
}
