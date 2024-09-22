#pragma once

#include <map>
#include <string>
#include <string_view>
#include <utility>

namespace hobby {

// Function to enumerate all fonts in a directory
auto enumerateFonts(std::string_view directory)
    -> std::map<std::string, std::string>;

/**
 * @brief Splits the font name into family and style based on the delimiter '-'.
 *
 * If the delimiter is not found, "Regular" is assumed as the style.
 *
 * @param font The full font name as a string.
 * @return A pair of strings: the first element is the font family, and the
 * second is the style.
 */
auto splitFontName(const std::string& font)
    -> std::pair<std::string, std::string>;

/**
 * @brief Organizes fonts into a map of font families and their styles.
 *
 * This function takes a map of font paths and organizes them by splitting the
 * font name into family and style, then groups them accordingly.
 *
 * @param fonts A map where the key is the font name, and the value is the file
 * path.
 * @return A map where the key is the font family, and the value is another map
 * of styles and their corresponding file paths.
 */
auto organizedFonts(const std::map<std::string, std::string>& fonts)
    -> std::map<std::string, std::map<std::string, std::string>>;

}  // namespace hobby
