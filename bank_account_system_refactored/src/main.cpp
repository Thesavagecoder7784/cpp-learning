#include <iostream>
#include <vector>
#include <string>
#include "BankAccount.h"
#include "utils.h"

int main() {
    std::cout << "--- Simple C++ Bank Account Management System ---" << std::endl;
    std::cout << "Demonstrates C++ OOP, Classes, Objects, Methods, Constructors, Access Specifiers, and Encapsulation." << std::endl;

    std::vector<BankAccount> accounts;
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
            case 1: {
                std::cout << "\n--- Create New Account ---" << std::endl;
                std::string holderName = getStringInput("Enter account holder's name: ");
                double initialBalance = getDoubleInput("Enter initial balance: $");

                std::string newAccNum = "ACC" + std::to_string(nextAccountNumber++);
                BankAccount newAccount(newAccNum, holderName, initialBalance);
                accounts.push_back(newAccount);
                std::cout << "Account created successfully! Account Number: " << newAccNum << std::endl;
                break;
            }
            case 2: {
                std::cout << "\n--- Deposit Funds ---" << std::endl;
                std::string accNum = getStringInput("Enter account number: ");
                double amount = getDoubleInput("Enter amount to deposit: $");

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
            case 3: {
                std::cout << "\n--- Withdraw Funds ---" << std::endl;
                std::string accNum = getStringInput("Enter account number: ");
                double amount = getDoubleInput("Enter amount to withdraw: $");

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
            case 5: {
                std::cout << "\n--- All Accounts ---" << std::endl;
                if (accounts.empty()) {
                    std::cout << "No accounts created yet." << std::endl;
                }
                else {
                    for (const BankAccount& acc : accounts) {
                        acc.displayAccountInfo();
                    }
                }
                break;
            }
            case 0: {
                std::cout << "\nExiting Bank Account Management System. Goodbye!" << std::endl;
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
