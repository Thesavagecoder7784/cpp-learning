#include "BankAccount.h"
#include <iostream>
#include <iomanip>

BankAccount::BankAccount(std::string accNum, std::string holderName, double initialBalance) {
    accountNumber = accNum;
    accountHolderName = holderName;
    if (initialBalance >= 0) {
        balance = initialBalance;
    } else {
        balance = 0.0;
        std::cout << "Warning: Initial balance cannot be negative. Setting to 0.0." << std::endl;
    }
    std::cout << "Account " << accountNumber << " created for " << accountHolderName << "." << std::endl;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited $" << std::fixed << std::setprecision(2) << amount
                  << ". New balance: $" << balance << std::endl;
    } else {
        std::cout << "Deposit amount must be positive." << std::endl;
    }
}

bool BankAccount::withdraw(double amount) {
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

double BankAccount::getBalance() const {
    return balance;
}

std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

void BankAccount::displayAccountInfo() const {
    std::cout << "\n--- Account Details ---" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolderName << std::endl;
    std::cout << "Balance:        $" << std::fixed << std::setprecision(2) << balance << std::endl;
    std::cout << "-----------------------" << std::endl;
}
