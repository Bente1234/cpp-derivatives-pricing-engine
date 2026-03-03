# C++ Derivatives Pricing Engine (European Options)

A compact C++17 project implementing **multiple pricing methods** for a European call option and benchmarking their **accuracy vs runtime**.

Implemented methods:
- **Black–Scholes (closed form)**
- **CRR binomial tree** (numerical convergence to Black–Scholes)
- **Monte Carlo (GBM)** under risk-neutral measure
- **Monte Carlo with antithetic variates** (variance reduction)

---

## Model

Under risk-neutral GBM:
\[
S_T = S_0 \exp\left((r - \tfrac{1}{2}\sigma^2)T + \sigma\sqrt{T}Z\right),\quad Z\sim\mathcal{N}(0,1)
\]

European call payoff:
\[
\max(S_T - K, 0)
\]

---

## Build & Run (CMake)

From the repository root:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
cmake --build .