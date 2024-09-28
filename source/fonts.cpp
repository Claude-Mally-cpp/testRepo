#include <filesystem>
#include <hobby/fonts.hpp>
#include <ranges>
#include <vector>

namespace fs = std::filesystem;

namespace hobby {

#include <string>

const std::string hobbyFontsDirectory = "./fonts";

auto getFontDirectories() -> std::vector<std::filesystem::path> {
    std::vector<std::filesystem::path> fontDirs;
    fontDirs.emplace_back(hobbyFontsDirectory);

#ifdef _WIN32
    // Windows
    fontDirs.emplace_back("C:\\Windows\\Fonts");
#elif __APPLE__
    // macOS
    fontDirs.emplace_back("/Library/Fonts");
    fontDirs.emplace_back("/System/Library/Fonts");
    fontDirs.emplace_back(std::filesystem::path(getenv("HOME")) /
                          "Library/Fonts");
#elif __linux__
    // Linux
    fontDirs.emplace_back("/usr/share/fonts");
    fontDirs.emplace_back("/usr/local/share/fonts");
    fontDirs.emplace_back(std::filesystem::path(getenv("HOME")) / ".fonts");
#endif

    return fontDirs;
}

auto enumerateFonts(StringLikeRange auto directories)
    -> std::map<std::string, std::string> {
    std::map<std::string, std::string> fontMap;

    // Combine user-specified directories with system directories
    auto fontsDirectories = getFontDirectories();
    fontsDirectories.insert(fontsDirectories.end(), directories.begin(),
                            directories.end());

    // Lambda to process each directory and add fonts to fontMap
    auto processDirectory = [&](const auto& directory) {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string extension = entry.path().extension().string();

                if (extension == ".ttf" || extension == ".otf") {
                    std::string fontName =
                        entry.path().stem().string();  // Font name
                    fontMap[fontName] = fs::absolute(entry.path()).string();
                }
            }
        }
    };

    for (const auto& directory : fontsDirectories) {
        processDirectory(directory);
    }

    return fontMap;
}

auto enumerateFonts() -> std::map<std::string, std::string> {
    std::vector<const char*> emptyUserPaths;
    return enumerateFonts(emptyUserPaths);
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
    transformedFonts.reserve(fonts.size());
    for (const auto& [fontName, path] : fonts) {
        transformedFonts.emplace_back(splitFontName(fontName), path);
    }

    std::map<std::string, std::map<std::string, std::string>> fontMap;
    for (const auto& [familyStyle, path] : transformedFonts | std::views::all) {
        const auto& [family, style] = familyStyle;
        fontMap[family][style] = path;
    }

    return fontMap;
}

}  // namespace hobby
