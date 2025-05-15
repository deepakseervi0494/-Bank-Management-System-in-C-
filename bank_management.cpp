#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account {
private:
    int accNumber;
    char name[50];
    char type;
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void deposit(float);
    void withdraw(float);
    void report() const;
    int getAccNumber() const;
    float getBalance() const;
    char getType() const;
};

void Account::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter Account Type (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter Initial Amount (>=500 for Saving and >=1000 for Current): ";
    cin >> balance;
    cout << "\nAccount Created Successfully!\n";
}

void Account::showAccount() const {
    cout << "\nAccount No.: " << accNumber;
    cout << "\nAccount Holder Name: " << name;
    cout << "\nType of Account: " << type;
    cout << "\nBalance Amount: " << balance << endl;
}

void Account::modify() {
    cout << "Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Modify Type of Account: ";
    cin >> type;
    type = toupper(type);
    cout << "Modify Balance Amount: ";
    cin >> balance;
}

void Account::deposit(float amt) {
    balance += amt;
}

void Account::withdraw(float amt) {
    balance -= amt;
}

void Account::report() const {
    cout << accNumber << setw(15) << name << setw(10) << type << setw(10) << balance << endl;
}

int Account::getAccNumber() const {
    return accNumber;
}

float Account::getBalance() const {
    return balance;
}

char Account::getType() const {
    return type;
}

// File functions
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int, int);

int main() {
    int choice;
    int num;

    do {
        cout << "\n\n\t--- BANK MANAGEMENT SYSTEM ---";
        cout << "\n\n\t1. New Account";
        cout << "\n\t2. Deposit Amount";
        cout << "\n\t3. Withdraw Amount";
        cout << "\n\t4. Balance Enquiry";
        cout << "\n\t5. All Account Holder List";
        cout << "\n\t6. Close An Account";
        cout << "\n\t7. Modify An Account";
        cout << "\n\t8. Exit";
        cout << "\n\n\tSelect Your Option (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1: writeAccount(); break;
            case 2:
                cout << "Enter Account No.: ";
                cin >> num;
                depositWithdraw(num, 1);
                break;
            case 3:
                cout << "Enter Account No.: ";
                cin >> num;
                depositWithdraw(num, 2);
                break;
            case 4:
                cout << "Enter Account No.: ";
                cin >> num;
                displayAccount(num);
                break;
            case 5: displayAll(); break;
            case 6:
                cout << "Enter Account No.: ";
                cin >> num;
                deleteAccount(num);
                break;
            case 7:
                cout << "Enter Account No.: ";
                cin >> num;
                modifyAccount(num);
                break;
            case 8:
                cout << "Thanks for using the bank management system.\n";
                break;
            default:
                cout << "Invalid option! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}

// Create account
void writeAccount() {
    Account ac;
    ofstream outFile("account.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
    outFile.close();
}

// Read single account
void displayAccount(int n) {
    Account ac;
    bool found = false;
    ifstream inFile("account.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccNumber() == n) {
            ac.showAccount();
            found = true;
        }
    }
    inFile.close();
    if (!found) cout << "\nAccount not found.\n";
}

// Modify account
void modifyAccount(int n) {
    Account ac;
    fstream File("account.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (!File.eof() && !found) {
        streampos pos = File.tellg();
        File.read(reinterpret_cast<char*>(&ac), sizeof(Account));
        if (ac.getAccNumber() == n) {
            ac.showAccount();
            cout << "\nEnter New Details:\n";
            ac.modify();
            File.seekp(pos);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "\nRecord Updated.\n";
            found = true;
        }
    }
    File.close();
    if (!found) cout << "\nRecord not found.\n";
}

// Delete account
void deleteAccount(int n) {
    Account ac;
    ifstream inFile("account.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccNumber() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("temp.dat", "account.dat");
    cout << "\nRecord Deleted.\n";
}

// Display all accounts
void displayAll() {
    Account ac;
    ifstream inFile("account.dat", ios::binary);
    cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
    cout << "=========================================\n";
    cout << "A/c no.      NAME        Type    Balance\n";
    cout << "=========================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

// Deposit / Withdraw
void depositWithdraw(int n, int option) {
    float amt;
    Account ac;
    fstream File("account.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (!File.eof() && !found) {
        streampos pos = File.tellg();
        File.read(reinterpret_cast<char*>(&ac), sizeof(Account));
        if (ac.getAccNumber() == n) {
            ac.showAccount();
            if (option == 1) {
                cout << "Enter amount to deposit: ";
                cin >> amt;
                ac.deposit(amt);
            } else {
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                if (amt > ac.getBalance()) {
                    cout << "Insufficient balance.\n";
                } else {
                    ac.withdraw(amt);
                }
            }
            File.seekp(pos);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "\nTransaction Successful.\n";
            found = true;
        }
    }
    File.close();
    if (!found) cout << "\nRecord Not Found.\n";
}
