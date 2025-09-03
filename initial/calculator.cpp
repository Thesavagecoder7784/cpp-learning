// cpp_learning_project.cpp
// A simple command-line utility to demonstrate C++ functions, overloading, scope, recursion, and lambdas

#include <iostream>  
#include <string>     
#include <vector>    
#include <functional> 
#include <limits>     
#include <numeric>   
#include <algorithm>  

// --- Global Variable (Demonstrates Global Scope) ---
int operationCounter = 0;

// Function to get a valid integer input from the user.
int getIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { 
            std::cout << "Invalid input. Please enter a whole number." << std::endl;
            std::cin.clear(); 
            // Ignore the rest of the invalid line to prevent an infinite loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to get a valid double input from the user.
double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to get a string input from the user, handling spaces.
std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value); 
    return value;
}

// --- 1. C++ Functions (Basic Arithmetic Operations) ---

// Function to add two integers.
int add(int a, int b) {
    operationCounter++;
    return a + b;
}

// Function to subtract two integers.
int subtract(int a, int b) {
    operationCounter++;
    return a - b;
}

// Function to multiply two integers.
int multiply(int a, int b) {
    operationCounter++;
    return a * b;
}

// Function to divide two integers. Handles division by zero.
double divide(int a, int b) {
    operationCounter++;
    if (b == 0) {
        std::cout << "Error: Division by zero is not allowed." << std::endl;
        return 0.0; // Return 0.0 or throw an exception in a real application
    }
    return static_cast<double>(a) / b; // Cast to double for floating-point division
}

// --- 2. C++ Function Overloading (for 'add' with different types) ---

// Overloaded function: Adds two doubles.
double add(double a, double b) {
    operationCounter++;
    return a + b;
}

// --- 3. C++ Scope Demonstration ---
// This function demonstrates different variable scopes: global, local, and block.
void demonstrateScope() {
    std::cout << "\n--- Demonstrating C++ Scope ---" << std::endl;

    // Local Scope: 'localVariable' is only accessible within this function.
    int localVariable = 100;
    std::cout << "Inside demonstrateScope(): localVariable = " << localVariable << std::endl;
    // Accessing the global variable 'operationCounter' from within this function.
    std::cout << "Inside demonstrateScope(): global operationCounter = " << operationCounter << std::endl;

    // Block Scope: 'blockVariable' is only accessible within this 'if' block.
    if (true) {
        int blockVariable = 200;
        std::cout << "Inside if block: blockVariable = " << blockVariable << std::endl;
        std::cout << "Inside if block: localVariable (from outer scope) = " << localVariable << std::endl;
    }

    // Another Block Scope: 'loopVariable' is only accessible within this 'for' loop.
    for (int loopVariable = 0; loopVariable < 2; ++loopVariable) {
        std::cout << "Inside for loop: loopVariable = " << loopVariable << std::endl;
    }

    std::cout << "Exiting scope demonstration." << std::endl;
}

// --- 4. C++ Recursion (Factorial Calculation) ---

// Recursive function to calculate the factorial of a non-negative integer.
// Factorial of n (n!) is the product of all positive integers less than or equal to n.

long long factorial(int n) {
    operationCounter++;
    if (n < 0) {
        std::cout << "Error: Factorial is not defined for negative numbers." << std::endl;
        return -1; 
    }
    // Base case: The condition that stops the recursion.
    if (n == 0) {
        return 1;
    }
    // Recursive step: The function calls itself with a smaller input.
    else {
        return n * factorial(n - 1);
    }
}

// --- 5. C++ Lambdas (List Processing) ---

void demonstrateLambdasForListProcessing() {
    std::cout << "\n--- Demonstrating Lambdas for List Processing ---" << std::endl;
    operationCounter++;

    std::vector<int> numbers;
    std::cout << "Enter a list of integers (enter 0 to stop):" << std::endl;
    int num;
    while ((num = getIntegerInput("Enter number: ")) != 0) {
        numbers.push_back(num);
    }

    if (numbers.empty()) {
        std::cout << "No numbers entered. Skipping list processing." << std::endl;
        return;
    }

    // Lambda 1: A simple lambda to print each element of the vector.
    std::cout << "Original list: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;

    // Lambda 2: Calculate the sum of all numbers using std::accumulate and a lambda.
    long long totalSum = std::accumulate(numbers.begin(), numbers.end(), 0LL,
                                         [](long long currentSum, int n) {
                                             return currentSum + n;
                                         });
    std::cout << "Sum of all numbers: " << totalSum << std::endl;

    // Lambda 3: Calculate the sum of only even numbers using std::for_each and a lambda with capture.
    long long evenSum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&](int n) {
        if (n % 2 == 0) {
            evenSum += n; 
        }
    });
    std::cout << "Sum of even numbers: " << evenSum << std::endl;

    // Lambda 4: Using a lambda to filter and print numbers greater than a user-defined threshold.
    int threshold = getIntegerInput("Enter a threshold to find numbers greater than it: ");
    std::cout << "Numbers greater than " << threshold << ": ";
    std::for_each(numbers.begin(), numbers.end(), [threshold](int n) {
        if (n > threshold) {
            std::cout << n << " ";
        }
    });
    std::cout << std::endl;

    // Lambda 5: Storing a lambda in std::function for later use.
    std::function<bool(int)> isPrime = [](int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) return false;
        }
        return true;
    };

    std::cout << "Prime numbers in the list: ";
    std::for_each(numbers.begin(), numbers.end(), [&](int n) {
        if (isPrime(n)) { // Use the stored lambda
            std::cout << n << " ";
        }
    });
    std::cout << std::endl;
}

// --- Main Function (Entry point of the program) ---
int main() {
    std::cout << "--- Simple C++ Math & Data Utility ---" << std::endl;
    std::cout << "This utility demonstrates C++ functions, overloading, scope, recursion, and lambdas." << std::endl;

    int choice;
    do {
        std::cout << "\n--- Main Menu ---" << std::endl;
        std::cout << "1. Basic Calculator Operations" << std::endl;
        std::cout << "2. Calculate Factorial (Recursion)" << std::endl;
        std::cout << "3. Process List of Numbers (Lambdas)" << std::endl;
        std::cout << "4. Demonstrate C++ Scope" << std::endl;
        std::cout << "0. Exit" << std::endl;
        choice = getIntegerInput("Enter your choice: ");

        switch (choice) {
            case 1: { // Basic Calculator Operations
                std::cout << "\n--- Basic Calculator ---" << std::endl;
                int opChoice;
                do {
                    std::cout << "\nCalculator Menu:" << std::endl;
                    std::cout << "  1. Add Integers" << std::endl;
                    std::cout << "  2. Add Doubles (Overloaded)" << std::endl;
                    std::cout << "  3. Subtract Integers" << std::endl;
                    std::cout << "  4. Multiply Integers" << std::endl;
                    std::cout << "  5. Divide Integers" << std::endl;
                    std::cout << "  0. Back to Main Menu" << std::endl;
                    opChoice = getIntegerInput("Select operation: ");

                    if (opChoice == 1) {
                        int a = getIntegerInput("Enter first integer: ");
                        int b = getIntegerInput("Enter second integer: ");
                        std::cout << "Result: " << a << " + " << b << " = " << add(a, b) << std::endl;
                    } else if (opChoice == 2) {
                        double a = getDoubleInput("Enter first double: ");
                        double b = getDoubleInput("Enter second double: ");
                        std::cout << "Result: " << a << " + " << b << " = " << add(a, b) << std::endl; // Calls overloaded add
                    } else if (opChoice == 3) {
                        int a = getIntegerInput("Enter first integer: ");
                        int b = getIntegerInput("Enter second integer: ");
                        std::cout << "Result: " << a << " - " << b << " = " << subtract(a, b) << std::endl;
                    } else if (opChoice == 4) {
                        int a = getIntegerInput("Enter first integer: ");
                        int b = getIntegerInput("Enter second integer: ");
                        std::cout << "Result: " << a << " * " << b << " = " << multiply(a, b) << std::endl;
                    } else if (opChoice == 5) {
                        int a = getIntegerInput("Enter numerator (integer): ");
                        int b = getIntegerInput("Enter denominator (integer): ");
                        std::cout << "Result: " << a << " / " << b << " = " << divide(a, b) << std::endl;
                    } else if (opChoice != 0) {
                        std::cout << "Invalid calculator option. Please try again." << std::endl;
                    }
                } while (opChoice != 0);
                break;
            }
            case 2: { // Calculate Factorial (Recursion)
                std::cout << "\n--- Factorial Calculator ---" << std::endl;
                int num = getIntegerInput("Enter a non-negative integer for factorial: ");
                long long result = factorial(num);
                if (result != -1) { 
                    std::cout << "Factorial of " << num << " is: " << result << std::endl;
                }
                break;
            }
            case 3: { // Process List of Numbers (Lambdas)
                demonstrateLambdasForListProcessing();
                break;
            }
            case 4: { // Demonstrate C++ Scope
                demonstrateScope();
                std::cout << "Back in Main Menu: Global operationCounter = " << operationCounter << std::endl;
                break;
            }
            case 0: { // Exit
                std::cout << "\nExiting Simple C++ Math & Data Utility. Total operations performed: " << operationCounter << std::endl;
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a number from the menu." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
