#include <iostream>
#include "option_types.hpp"
#include "black_scholes.hpp"

int main() {
    OptionParams p{100.0, 100.0, 0.02, 0.20, 1.0};

    try {
        p.validate();
        auto bs = black_scholes_call(p);

        std::cout << bs.method << " call price: " << bs.price
                  << " | runtime_ms: " << bs.runtime_ms << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
