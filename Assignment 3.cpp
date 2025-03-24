#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

class NegativeDepositException : public runtime_error {
public:
  NegativeDepositException()
      : runtime_error("Can't deposit a negative amount!") {}
};

class OverdrawException : public runtime_error {
public:
  OverdrawException() : runtime_error("Insufficient funds!") {}
};

class InvalidAccountOperationException : public runtime_error {
public:
  InvalidAccountOperationException()
      : runtime_error("This account is closed!") {}
};

class BankAccount {
private:
  string accountNumber;
  double balance;
  bool isActive;

public:
  // Constructor to initialize account number, balance, and active status
  BankAccount(string accNum, double initialBalance)
      : accountNumber(accNum), balance(initialBalance), isActive(true) {}

  // Deposit method
  void deposit(double amount) {
    if (!isActive) {
      throw InvalidAccountOperationException();
    }
    if (amount < 0) {
      throw NegativeDepositException();
    }
    balance += amount;
  }

  // Withdraw method
  void withdraw(double amount) {
    if (!isActive) {
      throw InvalidAccountOperationException();
    }
    if (amount > balance) {
      throw OverdrawException();
    }
    balance -= amount;
  }

  // Method to get current balance
  double getBalance() const {
    if (!isActive) {
      throw InvalidAccountOperationException();
    }
    return balance;
  }

  // Method to close the account
  void closeAccount() { isActive = false; }
};

// Functions
void displayMenu();

int main() {
  try {
    // user enters an initial balance / create BankAccount object using smart
    // pointers
    cout << "Enter initial balance: ";
    double initialBalance;
    cin >> initialBalance;

    auto account = make_unique<BankAccount>(
        "123456", initialBalance); // Example initialization

    cout << "Bank Account Created: #"
         << "123456" << endl;

    while (true) {
      displayMenu(); // Menu of choices for user to select in bank account
                     // management system
      int choice;
      cin >> choice;

      switch (choice) {
      case 1: // deposit money
        // user enters deposit amount
        cout << "\nEnter deposit amount :" << endl;
        double deposit;
        cin >> deposit;
        cout << "\nDepositing $" << deposit << "..." << endl;
        account->deposit(deposit);
        break;
      case 2: // withdraw money
        // user enters withdrawal amount
        cout << "\nEnter withdraw amount :" << endl;
        double withdraw;
        cin >> withdraw;
        cout << "\nDepositing $" << withdraw << "..." << endl;
        account->withdraw(withdraw);
        break;
      case 3: // check account balance
        cout << "\nCurrent Balance: $" << account->getBalance() << endl;
        break;
      case 4: // close account
        account->closeAccount();
        break;
      case 5: // quit program
        cout << "\nThank you for using the Bank!\n";
        return 0;
      default:
        cout << "\nInvalid choice. Please try again.\n";
      }
    }

  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}

void displayMenu() {
  cout << "\nWelcome to the Bank" << endl;
  cout << "1. Deposit Funds\n";
  cout << "2. Withdraw Funds\n";
  cout << "3. Check Balance\n";
  cout << "4. Close Account\n";
  cout << "5. Exit\n";
  cout << "Enter your choice: ";
}