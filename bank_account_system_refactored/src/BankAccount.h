#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    // Parameterized Constructor
    BankAccount(std::string accNum, std::string holderName, double initialBalance);

    // Method to deposit funds
    void deposit(double amount);

    // Method to withdraw funds
    bool withdraw(double amount);

    // Getter for the current balance
    double getBalance() const;

    // Getter for the account number
    std::string getAccountNumber() const;

    // Getter for the account holder name
    std::string getAccountHolderName() const;

    // Method to display all account information
    void displayAccountInfo() const;
};

#endif // BANK_ACCOUNT_H
