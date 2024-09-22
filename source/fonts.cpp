#include <filesystem>
#include <hobby/fonts.hpp>
#include <ranges>

namespace fs = std::filesystem;

namespace hobby {

auto enumerateFonts(std::string_view directory)
    -> std::map<std::string, std::string> {
    std::map<std::string, std::string> fontMap;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string extension = entry.path().extension().string();

            if (extension == ".ttf" ||
                extension == ".otf") {  // Assuming only .ttf and .otf fonts
                std::string fontName =
                    entry.path()
                        .stem()
                        .string();  // Font name without extension
                fontMap[fontName] = fs::absolute(entry.path())
                                        .string();  // Absolute path as value
            }
        }
    }

    return fontMap;
}

auto splitFontName(const std::string& font)
    -> std::pair<std::string, std::string> {
    auto pos = font.find('-');
    if (pos != std::string::npos) {
        return {font.substr(0, pos), font.substr(pos + 1)};
    }
    return {font, "Regular"};  // Default style if no '-' found
}

auto organizedFonts(const std::map<std::string, std::string>& fonts)
    -> std::map<std::string, std::map<std::string, std::string>> {
    // Convert the map into a vector of pairs (family, style)
    std::vector<std::pair<std::pair<std::string, std::string>, std::string>>
        transformedFonts;
    for (const auto& [fontName, path] : fonts) {
        transformedFonts.push_back({splitFontName(fontName), path});
    }

    std::map<std::string, std::map<std::string, std::string>> fontMap;
    for (const auto& [familyStyle, path] : transformedFonts | std::views::all) {
        const auto& [family, style] = familyStyle;
        fontMap[family][style] = path;
    }

    return fontMap;
}

}  // namespace hobby
