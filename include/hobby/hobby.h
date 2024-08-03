#pragma once

#include <cmath>
#include <string>

namespace hobby {

    /**  Language codes to be used with the Hobby class */
    enum class LanguageCode { EN, DE, ES, FR };

    /**
     * @brief A class for saying hello in multiple languages
     */
    class Hobby {
        std::string name;

      public:
        /**
         * @brief Creates a new hobby
         * @param name the name to greet
         */
        Hobby(std::string name);

        /**
         * @brief Creates a localized string containing the greeting
         * @param lang the language to greet in
         * @return a string containing the greeting
         */
        std::string greet(LanguageCode lang = LanguageCode::EN) const;
    };

}  // namespace hobby
