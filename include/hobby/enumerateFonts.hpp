#pragma once

#include <map>
#include <string_view>

namespace hobby {

// Function to enumerate all fonts in a directory
std::map<std::string, std::string> enumerateFonts(std::string_view directory);

}  // namespace hobby
