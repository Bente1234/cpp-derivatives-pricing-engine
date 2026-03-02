#pragma once
#include <stdexcept>
#include <string>

struct OptionParams {
    double S0;     // spot
    double K;      // strike
    double r;      // risk-free rate (annual, continuously compounded)
    double sigma;  // volatility (annual)
    double T;      // time to maturity (years)

    void validate() const {
        if (S0 <= 0.0) throw std::invalid_argument("S0 must be > 0");
        if (K  <= 0.0) throw std::invalid_argument("K must be > 0");
        if (sigma <= 0.0) throw std::invalid_argument("sigma must be > 0");
        if (T <= 0.0) throw std::invalid_argument("T must be > 0");
        // r can be negative; no restriction
    }
};

struct Result {
    double price = 0.0;
    double runtime_ms = 0.0; // wall-clock runtime in milliseconds
    std::string method;      // e.g., "Black-Scholes", "Binomial", "Monte Carlo"
};