#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

#include "option_types.hpp"
#include "black_scholes.hpp"
#include "binomial.hpp"
#include "monte_carlo.hpp"

static void print_summary(const OptionParams& p) {
    auto bs = black_scholes_call(p);
    auto bin = binomial_call_crr(p, 400);
    auto mc  = monte_carlo_call_gbm(p, 200000, 42u);
    auto av  = monte_carlo_call_gbm_antithetic(p, 200000, 42u);

    std::cout << "European Call Pricing (S0=" << p.S0
              << ", K=" << p.K
              << ", r=" << p.r
              << ", sigma=" << p.sigma
              << ", T=" << p.T << ")\n\n";

    std::cout << std::left
              << std::setw(24) << "Method"
              << std::setw(16) << "Price"
              << std::setw(16) << "AbsError"
              << std::setw(14) << "Runtime(ms)"
              << "\n";

    auto print_row = [&](const Result& res, double ref_price) {
        std::cout << std::left
                  << std::setw(24) << res.method
                  << std::setw(16) << res.price
                  << std::setw(16) << std::abs(res.price - ref_price)
                  << std::setw(14) << res.runtime_ms
                  << "\n";
    };

    print_row(bs, bs.price);
    print_row(bin, bs.price);
    print_row(mc,  bs.price);
    print_row(av,  bs.price);
}

static void print_sweeps(const OptionParams& p) {
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

    std::cout << "Monte Carlo convergence (baseline vs antithetic)\n";
    std::cout << std::left
              << std::setw(10) << "Paths"
              << std::setw(18) << "MC_Price"
              << std::setw(18) << "MC_AbsErr"
              << std::setw(14) << "MC_ms"
              << std::setw(18) << "AV_Price"
              << std::setw(18) << "AV_AbsErr"
              << std::setw(14) << "AV_ms"
              << "\n";

    for (int n : paths) {
        auto mc = monte_carlo_call_gbm(p, n, 42u);
        auto av = monte_carlo_call_gbm_antithetic(p, n, 42u);

        double err_mc = std::abs(mc.price - bs.price);
        double err_av = std::abs(av.price - bs.price);

        std::cout << std::left
                  << std::setw(10) << n
                  << std::setw(18) << mc.price
                  << std::setw(18) << err_mc
                  << std::setw(14) << mc.runtime_ms
                  << std::setw(18) << av.price
                  << std::setw(18) << err_av
                  << std::setw(14) << av.runtime_ms
                  << "\n";
    }
}

int main(int argc, char** argv) {
    OptionParams p{100.0, 100.0, 0.02, 0.20, 1.0};

    try {
        // Default mode: summary table
        // Optional: run sweeps by calling: pricing_engine --sweep
        if (argc >= 2 && std::string(argv[1]) == "--sweep") {
            print_sweeps(p);
        } else {
            print_summary(p);
            std::cout << "\nTip: run sweeps with: pricing_engine --sweep\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
