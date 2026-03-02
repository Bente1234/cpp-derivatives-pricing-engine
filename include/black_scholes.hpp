#pragma once
#include "option_types.hpp"

// Prices a European call option using the Black–Scholes closed-form formula.
Result black_scholes_call(const OptionParams& p);