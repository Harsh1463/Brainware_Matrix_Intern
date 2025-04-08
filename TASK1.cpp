// Create a fully functional ATM interface using C++

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>  //  for setprecision and fixed
using namespace std;

class ATM {
private:
    double balance;
    int pin;
    const int defaultPin = 1234; // This is a default pin
    static int transactionCount;

    // Function to clear input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Function to validate PIN
    bool validatePin(int enteredPin) {
        return enteredPin == pin;
    }

public:
    // Constructor
    ATM() {
        balance = 1000.00; // Starting balance
        pin = defaultPin;  
    }

    // Main menu display
    void displayMenu() {
        cout << "\n=== ATM Interface ===" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Change PIN" << endl;
        cout << "5. Transaction History" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
    }

    // Check balance
    void checkBalance() {
        cout << "\nCurrent Balance: $" << fixed << setprecision(2) << balance << endl;
        transactionCount++;
    }

    // Deposit money
    void deposit() {
        double amount;
        cout << "\nEnter amount to deposit: $";
        
        if (cin >> amount && amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << fixed << setprecision(2) << amount << endl;
            cout << "New Balance: $" << fixed << setprecision(2) << balance << endl;
            transactionCount++;
        } else {
            cout << "Invalid amount entered!" << endl;
            clearInputBuffer();
        }
    }

    // Withdraw money
    void withdraw() {
        double amount;
        cout << "\nEnter amount to withdraw: $";
        
        if (cin >> amount && amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                cout << "Please take your cash: $" << fixed << setprecision(2) << amount << endl;
                cout << "Remaining Balance: $" << fixed << setprecision(2) << balance << endl;
                transactionCount++;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        } else {
            cout << "Invalid amount entered!" << endl;
            clearInputBuffer();
        }
    }

    // Change PIN
    void changePin() {
        int oldPin, newPin;
        cout << "\nEnter current PIN: ";
        
        if (cin >> oldPin) {
            if (validatePin(oldPin)) {
                cout << "Enter new PIN: ";
                if (cin >> newPin && newPin >= 1000 && newPin <= 9999) {
                    pin = newPin;
                    cout << "PIN successfully changed!" << endl;
                    transactionCount++;
                } else {
                    cout << "New PIN must be 4 digits!" << endl;
                    clearInputBuffer();
                }
            } else {
                cout << "Incorrect PIN!" << endl;
            }
        }
    }

    // Show transaction count
    void showTransactionHistory() {
        cout << "\nTotal transactions performed: " << transactionCount << endl;
    }

    // Main ATM operation
    void run() {
        int enteredPin;
        cout << "Welcome to the ATM" << endl;
        cout << "Enter your PIN: ";
        
        if (cin >> enteredPin && validatePin(enteredPin)) {
            int choice;
            do {
                displayMenu();
                if (cin >> choice) {
                    switch (choice) {
                        case 1:
                            checkBalance();
                            break;
                        case 2:
                            deposit();
                            break;
                        case 3:
                            withdraw();
                            break;
                        case 4:
                            changePin();
                            break;
                        case 5:
                            showTransactionHistory();
                            break;
                        case 6:
                            cout << "\nThank you for using our ATM. Goodbye!" << endl;
                            return;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                    }
                } else {
                    cout << "Invalid input! Please enter a number." << endl;
                    clearInputBuffer();
                }
            } while (true);
        } else {
            cout << "Invalid PIN! Access denied." << endl;
            clearInputBuffer();
        }
    }
};

// Initialize static member
int ATM::transactionCount = 0;

int main() {
    ATM atm;
    atm.run();
    return 0;
}