#include <iostream>
#include "option_types.hpp"
#include "black_scholes.hpp"
#include "binomial.hpp"

int main() {
    OptionParams p{100.0, 100.0, 0.02, 0.20, 1.0};

    try {
        auto bs = black_scholes_call(p);
        auto bin = binomial_call_crr(p, 200);

        std::cout << bs.method << " price: " << bs.price
                  << " | runtime_ms: " << bs.runtime_ms << std::endl;

        std::cout << bin.method << " price: " << bin.price
                  << " | runtime_ms: " << bin.runtime_ms << std::endl;

        std::cout << "Absolute difference: "
                  << std::abs(bs.price - bin.price) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}