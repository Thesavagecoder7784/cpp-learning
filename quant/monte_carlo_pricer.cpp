
// monte_carlo_pricer.cpp
// A basic C++ program to simulate future stock prices using a Monte Carlo method.
// This demonstrates a fundamental concept in quantitative finance.

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <numeric>      // For std::accumulate
#include <algorithm>    // For std::min_element and std::max_element
#include <iomanip>      // For std::fixed and std::setprecision

/**
 * @brief Runs a single stock price simulation path using Geometric Brownian Motion.
 * 
 * @param S0 Initial stock price.
 * @param mu The drift (expected annual return).
 * @param sigma The volatility (annual standard deviation of returns).
 * @param T The time horizon in years.
 * @param steps The number of time steps in the simulation.
 * @param generator A reference to the random number generator.
 * @param distribution A reference to the normal distribution.
 * @return The final simulated stock price at the end of the time horizon.
 */
double run_single_simulation(double S0, double mu, double sigma, double T, int steps, 
                             std::mt19937& generator, std::normal_distribution<>& distribution) {
    
    double dt = T / steps; // The size of a single time step
    double price = S0;

    for (int i = 0; i < steps; ++i) {
        // Generate a random number from the standard normal distribution (Z)
        double Z = distribution(generator);
        
        // Apply the Geometric Brownian Motion formula
        // S_t = S_{t-1} * exp( (mu - 0.5 * sigma^2) * dt + sigma * Z * sqrt(dt) )
        price *= std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * Z * std::sqrt(dt));
    }

    return price;
}

int main() {
    // --- 1. DEFINE SIMULATION PARAMETERS ---
    double S0 = 100.0;              // Initial stock price
    double mu = 0.05;               // Expected annual return (5%)
    double sigma = 0.20;            // Annual volatility (20%)
    double T = 1.0;                 // Time horizon in years (1 year)
    int num_simulations = 10000;    // Number of Monte Carlo simulations to run
    int steps = 252;                // Number of time steps (e.g., trading days in a year)

    std::cout << "--- Monte Carlo Stock Price Simulator ---" << std::endl;
    std::cout << "Running " << num_simulations << " simulations..." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Initial Price: $" << std::fixed << std::setprecision(2) << S0 << std::endl;
    std::cout << "Expected Return (Drift): " << mu * 100.0 << "%" << std::endl;
    std::cout << "Volatility: " << sigma * 100.0 << "%" << std::endl;
    std::cout << "Time Horizon: " << T << " year(s)" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;


    // --- 2. SETUP RANDOM NUMBER GENERATION ---
    // Use the Mersenne Twister engine for high-quality random numbers
    std::mt19937 generator(std::random_device{}()); 
    // Standard normal distribution (mean=0.0, stddev=1.0)
    std::normal_distribution<> distribution(0.0, 1.0);


    // --- 3. RUN THE SIMULATIONS ---
    std::vector<double> final_prices;
    final_prices.reserve(num_simulations); // Pre-allocate memory for efficiency

    for (int i = 0; i < num_simulations; ++i) {
        double final_price = run_single_simulation(S0, mu, sigma, T, steps, generator, distribution);
        final_prices.push_back(final_price);
    }


    // --- 4. ANALYZE THE RESULTS ---
    // Calculate the average of all simulated final prices
    double sum_of_prices = std::accumulate(final_prices.begin(), final_prices.end(), 0.0);
    double average_price = sum_of_prices / num_simulations;

    // Find the minimum and maximum simulated prices
    double min_price = *std::min_element(final_prices.begin(), final_prices.end());
    double max_price = *std::max_element(final_prices.begin(), final_prices.end());


    // --- 5. DISPLAY THE RESULTS ---
    std::cout << "--- Simulation Results ---" << std::endl;
    std::cout << "Average Simulated Final Price: $" << std::fixed << std::setprecision(2) << average_price << std::endl;
    std::cout << "Minimum Simulated Final Price: $" << std::fixed << std::setprecision(2) << min_price << std::endl;
    std::cout << "Maximum Simulated Final Price: $" << std::fixed << std::setprecision(2) << max_price << std::endl;
    std::cout << "--------------------------" << std::endl;

    // A simple example of how this can be used for option pricing:
    // Calculate the probability of the stock price ending above a certain strike price
    double strike_price = 110.0;
    int count_above_strike = 0;
    for (double price : final_prices) {
        if (price > strike_price) {
            count_above_strike++;
        }
    }
    double probability_above_strike = static_cast<double>(count_above_strike) / num_simulations;

    std::cout << "--- Basic Option Pricing Example ---" << std::endl;
    std::cout << "Probability of price > $" << strike_price << ": " 
              << std::fixed << std::setprecision(2) << probability_above_strike * 100.0 << "%" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    return 0;
}
