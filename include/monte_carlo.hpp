#pragma once
#include "option_types.hpp"

// Monte Carlo pricing for a European call under GBM (risk-neutral).
Result monte_carlo_call_gbm(const OptionParams& p, int n_paths, unsigned int seed);

// Monte Carlo with antithetic variates (variance reduction).
Result monte_carlo_call_gbm_antithetic(const OptionParams& p, int n_paths, unsigned int seed);