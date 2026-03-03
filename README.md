# C++ Derivatives Pricing Engine (European Options)

A compact C++17 project implementing multiple option pricing methodologies for a European call option and benchmarking their accuracy and computational performance.

The project focuses on numerical method comparison against analytical benchmarks, with explicit evaluation of convergence behaviour, estimator bias, and runtime trade-offs.

---

## Implemented Methods

- **Black–Scholes (closed form)** — analytical pricing benchmark  
- **CRR Binomial Tree** — discrete-time approximation with convergence analysis  
- **Monte Carlo (GBM)** — risk-neutral simulation under geometric Brownian motion  
- **Monte Carlo + Antithetic Variates** — variance reduction technique  

---

## Quantitative Focus

This project examines:

- Numerical convergence toward analytical solutions  
- Monte Carlo estimator behaviour under increasing sample size  
- Variance reduction efficiency (antithetic variates)  
- Accuracy vs computational cost trade-offs  

---

## Model

Risk-neutral geometric Brownian motion:

S_T = S0 * exp((r - 0.5 * sigma²) * T + sigma * sqrt(T) * Z)  
where Z ~ N(0,1)

European call payoff:

max(S_T - K, 0)

---

## Example Benchmark Output
