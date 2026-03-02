    #include "monte_carlo.hpp"
#include "timer.hpp"

#include <cmath>
#include <random>
#include <stdexcept>

Result monte_carlo_call_gbm(const OptionParams& p, int n_paths, unsigned int seed) {
    p.validate();
    if (n_paths <= 0) throw std::invalid_argument("n_paths must be > 0");

    Timer timer;

    const double S0 = p.S0;
    const double K  = p.K;
    const double r  = p.r;
    const double sig = p.sigma;
    const double T  = p.T;

    // Risk-neutral GBM: S_T = S0 * exp((r - 0.5*sigma^2)T + sigma*sqrt(T)*Z)
    const double drift = (r - 0.5 * sig * sig) * T;
    const double vol   = sig * std::sqrt(T);
    const double disc  = std::exp(-r * T);

    std::mt19937 rng(seed);
    std::normal_distribution<double> nd(0.0, 1.0);

    double payoff_sum = 0.0;

    for (int i = 0; i < n_paths; ++i) {
        const double Z = nd(rng);
        const double ST = S0 * std::exp(drift + vol * Z);
        const double payoff = std::max(ST - K, 0.0);
        payoff_sum += payoff;
    }

    const double price = disc * (payoff_sum / static_cast<double>(n_paths));

    Result res;
    res.method = "Monte Carlo (GBM)";
    res.price = price;
    res.runtime_ms = timer.elapsed_ms();
    return res;
}