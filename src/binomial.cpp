#include "binomial.hpp"
#include "timer.hpp"

#include <cmath>
#include <vector>
#include <algorithm>

Result binomial_call_crr(const OptionParams& p, int N) {
    p.validate();

    Timer timer;

    const double S = p.S0;
    const double K = p.K;
    const double r = p.r;
    const double sigma = p.sigma;
    const double T = p.T;

    const double dt = T / N;
    const double u = std::exp(sigma * std::sqrt(dt));
    const double d = 1.0 / u;
    const double disc = std::exp(-r * dt);
    const double q = (std::exp(r * dt) - d) / (u - d);

    std::vector<double> values(N + 1);

    // Terminal payoffs
    for (int i = 0; i <= N; ++i) {
        double ST = S * std::pow(u, N - i) * std::pow(d, i);
        values[i] = std::max(ST - K, 0.0);
    }

    // Backward induction
    for (int step = N - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            values[i] = disc * (q * values[i] + (1.0 - q) * values[i + 1]);
        }
    }

    Result res;
    res.method = "Binomial (CRR)";
    res.price = values[0];
    res.runtime_ms = timer.elapsed_ms();
    return res;
}