#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "option_types.hpp"
#include "black_scholes.hpp"
#include "binomial.hpp"
#include "monte_carlo.hpp"

int main() {
    OptionParams p{100.0, 100.0, 0.02, 0.20, 1.0};

    try {
        auto bs = black_scholes_call(p);

        std::cout << bs.method << " price: " << bs.price
                  << " | runtime_ms: " << bs.runtime_ms << "\n\n";

        // ---- Binomial sweep
        std::vector<int> steps = {25, 50, 100, 200, 400, 800};
        std::cout << "Binomial (CRR) convergence\n";
        std::cout << std::left
                  << std::setw(10) << "N"
                  << std::setw(18) << "Price"
                  << std::setw(18) << "AbsError"
                  << std::setw(14) << "Runtime(ms)"
                  << "\n";

        for (int N : steps) {
            auto bin = binomial_call_crr(p, N);
            double err = std::abs(bin.price - bs.price);

            std::cout << std::left
                      << std::setw(10) << N
                      << std::setw(18) << bin.price
                      << std::setw(18) << err
                      << std::setw(14) << bin.runtime_ms
                      << "\n";
        }

        std::cout << "\n";

        // ---- Monte Carlo sweep
        std::vector<int> paths = {1000, 5000, 20000, 100000, 300000};
        std::cout << "Monte Carlo (GBM) convergence\n";
        std::cout << std::left
                  << std::setw(12) << "Paths"
                  << std::setw(18) << "Price"
                  << std::setw(18) << "AbsError"
                  << std::setw(14) << "Runtime(ms)"
                  << "\n";

        for (int n : paths) {
            auto mc = monte_carlo_call_gbm(p, n, 42u);
            double err = std::abs(mc.price - bs.price);

            std::cout << std::left
                      << std::setw(12) << n
                      << std::setw(18) << mc.price
                      << std::setw(18) << err
                      << std::setw(14) << mc.runtime_ms
                      << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}