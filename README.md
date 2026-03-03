# C++ Derivatives Pricing Engine (European Options)

A compact C++17 project implementing **multiple pricing methods** for a European call option and benchmarking their **accuracy vs runtime**.

## Implemented Methods

- **Black–Scholes (closed form)** — analytical benchmark  
- **CRR Binomial Tree** — discrete-time approximation with convergence analysis  
- **Monte Carlo (GBM)** — risk-neutral simulation  
- **Monte Carlo + Antithetic Variates** — variance reduction technique

---
## Model

Risk-neutral geometric Brownian motion:

S_T = S0 * exp((r - 0.5 * sigma^2) * T + sigma * sqrt(T) * Z),  
where Z ~ N(0,1)

European call payoff:

max(S_T - K, 0)

---

## Build & Run (CMake)

From the repository root:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
cmake --build .
