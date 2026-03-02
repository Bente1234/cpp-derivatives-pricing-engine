#include "black_scholes.hpp"
#include "timer.hpp"

#include <cmath>
#include <stdexcept>

// Standard normal CDF using the error function
static double norm_cdf(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

Result black_scholes_call(const OptionParams& p) {
    p.validate();

    Timer timer;

    const double S = p.S0;
    const double K = p.K;
    const double r = p.r;
    const double sig = p.sigma;
    const double T = p.T;

    const double sqrtT = std::sqrt(T);

    // d1 = [ln(S/K) + (r + 0.5*sigma^2)T] / (sigma*sqrt(T))
    const double d1 = (std::log(S / K) + (r + 0.5 * sig * sig) * T) / (sig * sqrtT);
    const double d2 = d1 - sig * sqrtT;

    const double Nd1 = norm_cdf(d1);
    const double Nd2 = norm_cdf(d2);

    const double discK = K * std::exp(-r * T);
    const double price = S * Nd1 - discK * Nd2;

    Result res;
    res.method = "Black-Scholes";
    res.price = price;
    res.runtime_ms = timer.elapsed_ms();
    return res;
}