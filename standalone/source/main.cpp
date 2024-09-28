// #include <fmt/format.h>
#include <fmt/ranges.h>
#include <hobby/version.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <cxxopts.hpp>
#include <hobby/fonts.hpp>
#include <hobby/hobby.hpp>
#include <hobby/hobbyDice.hpp>
#include <hobby/hobbyMath.hpp>
#include <string>
#include <unordered_map>

using namespace std::literals;

void playWithWindow();

auto main(int argc, char** argv) -> int {
    using namespace std::literals::string_view_literals;
    try {
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
    ("r,random", "throw a N sided dice", cxxopts::value<uint64_t>())
    ("g,generate", "generate an array of 10 primes higher that argument", cxxopts::value<uint64_t>())
    ("w,window", "Open an SFML window")
    ("f,fonts", "enumerate installed fonts")
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

        if (result["window"].as<bool>()) {
            playWithWindow();
            return 0;
        }

        if (result["fonts"].as<bool>()) {
            auto fontMap = hobby::enumerateFonts();

            // get a map of <font name> and <map of <style name>, <full-path>
            auto organizedMap = hobby::organizedFonts(fontMap);
            for (const auto [familyName, styleMap] : organizedMap) {
                fmt::print("familyName {} styles: {{", familyName);
                fmt::print("{}", fmt::join(styleMap | std::views::keys, ", "));
                fmt::println("}}");
            }

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
            const auto numberOfPrimeToGenerate = 10;
            for (size_t index = 0; index < numberOfPrimeToGenerate; index++) {
                value = hobby::nextPrime(value);
                const auto divisors = hobby::getDivisors(value);
                assert(divisors.size() == 2);
                fmt::print("{}, ", value);
                value *= 3;
            }
            fmt::print("\n");
        }
        if (result.count("random")) {
            const auto diceSides = result["random"].as<uint64_t>();
            if (not diceSides) {
                fmt::println(stderr,
                             "random requires a non-zero number of dice sides");
                return -1;
            }
            const auto rollCount = 16;
            fmt::print("here are {} random values between 1 and {}: {{",
                       rollCount, diceSides);
            hobby::dice dice(diceSides);
            for (auto iteration = 0; iteration < rollCount; ++iteration) {
                const auto value = dice.roll();
                fmt::print("{}", value);
                if (iteration != (rollCount - 1)) {
                    fmt::print(", ");
                }
            }
            fmt::println("}}");
        }
    } catch (std::exception except) {
        fmt::println("caught exception {}", except.what());
    }
    return 0;
}

void playWithWindow() {
    auto title = fmt::format("Hobby window version {}", HOBBY_VERSION);
    const auto width = 800;
    const auto height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    auto fontMap = hobby::enumerateFonts();
    auto organizedMap = hobby::organizedFonts(fontMap);
    auto preferences = std::vector{"Arial", "Courier New", "Roboto"};
    auto preferedFontName = hobby::findFont(organizedMap, preferences);
    if (!preferedFontName) {
        fmt::println(stderr,
                     "Unable to locate one of the preferred fonts in [{}]\n",
                     fmt::join(preferences, ", "));
        return;
    }
    sf::Font font;
    if (!font.loadFromFile(*preferedFontName)) {
        fmt::println(stderr, "there was an error loading \"{}\"",
                     *preferedFontName);
    }
    fmt::println("loaded \"{}\"", *preferedFontName);

    auto testString = fmt::format("Hobby {}", *preferedFontName);

    sf::Text text;

    // select the font
    text.setFont(font);  // font is a sf::Font

    // set the string to display
    text.setString(testString);

    // set the character size
    text.setCharacterSize(24);  // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Italic);
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // clear the window with black color
            window.clear(sf::Color::Black);
            window.draw(text);

            // end the current frame
            window.display();
        }
    }
}