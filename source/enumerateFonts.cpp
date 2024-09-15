#include <filesystem>
#include <hobby/enumerateFonts.hpp>
#include <iostream>

namespace fs = std::filesystem;

namespace hobby {

std::map<std::string, std::string> enumerateFonts(std::string_view directory) {
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

}  // namespace hobby
