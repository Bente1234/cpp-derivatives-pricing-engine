cmake_minimum_required(VERSION 3.16)
project(CppDerivativesPricingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pricing_engine
    src/main.cpp
    src/black_scholes.cpp
    src/binomial.cpp
    src/monte_carlo.cpp
)

target_include_directories(pricing_engine PRIVATE include)