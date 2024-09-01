#include <concepts>
#include <optional>
#include <random>
#include <stdexcept>

namespace hobby {

template <std::unsigned_integral T = uint32_t>
class dice {
   public:
    // Constructor that accepts the number of sides as a runtime parameter
    explicit dice(T sides) : sides(sides), generator(randomDevice()) {
        if (sides == 0) {
            throw std::invalid_argument(
                "Number of sides must be greater than zero");
        }
    }

    // Method to roll the dice and get a random value between 1 and sides
    T roll() {
        if (!distribution.has_value()) {
            distribution.emplace(1, sides);
        }
        return (*distribution)(generator);
    }

    // Getter for the number of sides
    T getSides() const noexcept { return sides; }

   private:
    std::random_device randomDevice;
    std::mt19937 generator;
    std::optional<std::uniform_int_distribution<T>> distribution;
    T sides;
};

}  // end namespace hobby