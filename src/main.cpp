#include <iostream>
#include "option_types.hpp"

int main() {
    OptionParams p{100.0, 100.0, 0.02, 0.20, 1.0};
    try {
        p.validate();
        std::cout << "Inputs OK. Ready to price options." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Invalid inputs: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}