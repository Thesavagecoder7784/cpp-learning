// bank_account_system.cpp
#include <iostream> 
#include <string>
#include <vector>
#include <limits>
#include <iomanip> 

// Function to get a valid integer input from the user.
int getIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { // Check if input operation failed (e.g., non-numeric input)
            std::cout << "Invalid input. Please enter a whole number." << std::endl;
            std::cin.clear(); // Clear the error flag on std::cin
            // Ignore the rest of the invalid line to prevent an infinite loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Clear the remaining buffer after successful input (e.g., newline character)
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
    std::getline(std::cin, value); // Use getline to read entire line, including spaces
    return value;
}

// --- BankAccount Class Definition ---
// This class represents a single bank account.

class BankAccount {
private:
    // --- Access Specifiers: Private Members ---
    // These data members are private, meaning they can only be accessed or modified
    // by methods within the BankAccount class itself. This enforces Encapsulation.
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    // --- Constructors ---
    // A constructor is a special method called automatically when an object of the class is created.

    // Default Constructor: Initializes an account with default values.

    // Parameterized Constructor: Initializes an account with provided details.
    BankAccount(std::string accNum, std::string holderName, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = holderName;
        // Ensure initial balance is not negative
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            balance = 0.0;
            std::cout << "Warning: Initial balance cannot be negative. Setting to 0.0." << std::endl;
        }
        std::cout << "Account " << accountNumber << " created for " << accountHolderName << "." << std::endl;
    }

    // --- Class Methods (Public Interface) ---
    // Method to deposit funds into the account.
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << std::fixed << std::setprecision(2) << amount
                      << ". New balance: $" << balance << std::endl;
        } else {
            std::cout << "Deposit amount must be positive." << std::endl;
        }
    }

    // Method to withdraw funds from the account.
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be positive." << std::endl;
            return false;
        }
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew $" << std::fixed << std::setprecision(2) << amount
                      << ". New balance: $" << balance << std::endl;
            return true;
        } else {
            std::cout << "Insufficient funds. Current balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
            return false;
        }
    }

    // Method to get the current balance.
    // This is a "getter" method, providing read-only access to a private member.
    double getBalance() const { 
        return balance;
    }

    // Method to get the account number.
    std::string getAccountNumber() const {
        return accountNumber;
    }

    // Method to get the account holder name.
    std::string getAccountHolderName() const {
        return accountHolderName;
    }

    // Method to display all account information.
    void displayAccountInfo() const {
        std::cout << "\n--- Account Details ---" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolderName << std::endl;
        std::cout << "Balance:        $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
};

// --- Main Application Logic ---

int main() {
    std::cout << "--- Simple C++ Bank Account Management System ---" << std::endl;
    std::cout << "Demonstrates C++ OOP, Classes, Objects, Methods, Constructors, Access Specifiers, and Encapsulation." << std::endl;

    // A vector to store multiple BankAccount objects (our "database" of accounts).
    std::vector<BankAccount> accounts;
    // A simple counter to generate unique account numbers.
    int nextAccountNumber = 1001;

    int choice;
    do {
        std::cout << "\n--- Main Menu ---" << std::endl;
        std::cout << "1. Create New Account" << std::endl;
        std::cout << "2. Deposit Funds" << std::endl;
        std::cout << "3. Withdraw Funds" << std::endl;
        std::cout << "4. View Account Details" << std::endl;
        std::cout << "5. List All Accounts" << std::endl;
        std::cout << "0. Exit" << std::endl;
        choice = getIntegerInput("Enter your choice: ");

        switch (choice) {
            case 1: { // Create New Account
                std::cout << "\n--- Create New Account ---" << std::endl;
                std::string holderName = getStringInput("Enter account holder's name: ");
                double initialBalance = getDoubleInput("Enter initial balance: $");

                // --- Objects and Constructors ---
                // Creating a new BankAccount object (instance of the class).
                std::string newAccNum = "ACC" + std::to_string(nextAccountNumber++);
                BankAccount newAccount(newAccNum, holderName, initialBalance);
                accounts.push_back(newAccount); // Add the new account object to our vector
                std::cout << "Account created successfully! Account Number: " << newAccNum << std::endl;
                break;
            }
            case 2: { // Deposit Funds
                std::cout << "\n--- Deposit Funds ---" << std::endl;
                std::string accNum = getStringInput("Enter account number: ");
                double amount = getDoubleInput("Enter amount to deposit: $");

                // Find the account
                bool found = false;
                for (BankAccount& acc : accounts) {
                    if (acc.getAccountNumber() == accNum) { 
                        acc.deposit(amount);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 3: { // Withdraw Funds
                std::cout << "\n--- Withdraw Funds ---" << std::endl;
                std::string accNum = getStringInput("Enter account number: ");
                double amount = getDoubleInput("Enter amount to withdraw: $");

                // Find the account
                bool found = false;
                for (BankAccount& acc : accounts) {
                    if (acc.getAccountNumber() == accNum) {
                        acc.withdraw(amount);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\n--- View Account Details ---" << std::endl;
                std::string accNum = getStringInput("Enter account number: ");

                // Find the account
                bool found = false;
                for (const BankAccount& acc : accounts) { 
                    if (acc.getAccountNumber() == accNum) {
                        acc.displayAccountInfo(); 
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 5: { // List All Accounts
                std::cout << "\n--- All Accounts ---" << std::endl;
                if (accounts.empty()) {
                    std::cout << "No accounts created yet." << std::endl;
                } else {
                    for (const BankAccount& acc : accounts) {
                        acc.displayAccountInfo(); 
                    }
                }
                break;
            }
            case 0: { // Exit
                std::cout << "\nExiting Bank Account Management System. Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a number from the menu." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0; // Indicate successful program execution
}
