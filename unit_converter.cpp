// robust_unit_converter.cpp
#include <iostream>  
#include <string> 
#include <limits>   
#include <stdexcept> 
#include <iomanip>   

// Ensures the user enters a valid floating-point number.
double getIntegerInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { // Check if input operation failed (e.g., non-numeric input)
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag on std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { // Check if input operation failed (e.g., non-numeric input)
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag on std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// --- Conversion Functions with Exception Handling ---
// Converts Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    std::cerr << "DEBUG: Converting " << celsius << " C to F." << std::endl;
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Converts Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    std::cerr << "DEBUG: Converting " << fahrenheit << " F to C." << std::endl;
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Converts Kilometers to Miles
double kilometersToMiles(double km) {
    // --- C++ Error: Negative Distance ---
    if (km < 0) {
        std::cerr << "DEBUG: Negative distance provided for KM to Miles: " << km << std::endl;
        throw std::runtime_error("Distance cannot be negative.");
    }
    std::cerr << "DEBUG: Converting " << km << " KM to Miles." << std::endl;
    return km * 0.621371;
}

// Converts Miles to Kilometers
double milesToKilometers(double miles) {
    // --- C++ Error: Negative Distance ---
    if (miles < 0) {
        std::cerr << "DEBUG: Negative distance provided for Miles to KM: " << miles << std::endl;
        throw std::runtime_error("Distance cannot be negative.");
    }
    std::cerr << "DEBUG: Converting " << miles << " Miles to KM." << std::endl;
    return miles / 0.621371;
}

// --- Main Application Logic ---
int main() {
    std::cout << "--- Simple Robust Unit Converter ---" << std::endl;
    std::cout << "This tool demonstrates robust error handling, exceptions, and input validation." << std::endl;

    int choice;
    double valueToConvert;
    double convertedValue;

    do {
        std::cout << "\n--- Conversion Menu ---" << std::endl;
        std::cout << "1. Celsius to Fahrenheit" << std::endl;
        std::cout << "2. Fahrenheit to Celsius" << std::endl;
        std::cout << "3. Kilometers to Miles" << std::endl;
        std::cout << "4. Miles to Kilometers" << std::endl;
        std::cout << "0. Exit" << std::endl;

        // --- C++ Input Validation ---
        choice = getIntegerInput("Enter your choice: ");

        if (choice == 0) {
            break; // Exit the loop
        }

        // Validate choice range
        if (choice < 1 || choice > 4) {
            std::cout << "Invalid choice. Please select a number from the menu (1-4)." << std::endl;
            std::cerr << "DEBUG: User entered invalid menu choice: " << choice << std::endl;
            continue; // Go back to menu
        }

        // --- C++ Input Validation ---
        valueToConvert = getDoubleInput("Enter value to convert: ");

        // --- C++ Exceptions: Try-Catch Block for Conversions ---
        try {
            switch (choice) {
                case 1:
                    convertedValue = celsiusToFahrenheit(valueToConvert);
                    std::cout << std::fixed << std::setprecision(2) << valueToConvert << " C is "
                              << convertedValue << " F" << std::endl;
                    break;
                case 2:
                    convertedValue = fahrenheitToCelsius(valueToConvert);
                    std::cout << std::fixed << std::setprecision(2) << valueToConvert << " F is "
                              << convertedValue << " C" << std::endl;
                    break;
                case 3:
                    convertedValue = kilometersToMiles(valueToConvert); // May throw exception
                    std::cout << std::fixed << std::setprecision(2) << valueToConvert << " KM is "
                              << convertedValue << " Miles" << std::endl;
                    break;
                case 4:
                    convertedValue = milesToKilometers(valueToConvert); // May throw exception
                    std::cout << std::fixed << std::setprecision(2) << valueToConvert << " Miles is "
                              << convertedValue << " KM" << std::endl;
                    break;
                default:
                    // This case should ideally not be reached due to prior validation,
                    // but included for defensive programming.
                    std::cerr << "DEBUG: Unexpected default case in switch for choice: " << choice << std::endl;
                    std::cout << "An unexpected error occurred. Please try again." << std::endl;
                    break;
            }
        } catch (const std::runtime_error& e) {
            // Catch custom runtime errors (like negative distance)
            std::cout << "Conversion Error: " << e.what() << std::endl;
            std::cerr << "DEBUG: Caught runtime_error during conversion: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            // Catch any other unexpected standard exceptions
            std::cout << "An unexpected error occurred: " << e.what() << std::endl;
            std::cerr << "DEBUG: Caught generic std::exception: " << e.what() << std::endl;
        }

    } while (choice != 0);

    std::cout << "\nExiting Unit Converter. Goodbye!" << std::endl;
    return 0; // Indicate successful program execution
}
