

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;
public:
    BankAccount(int accNum, double initialBalance) {
        this->accountNumber = accNum;
        if (initialBalance < 0) {
            throw invalid_argument("начальный баланс не может быть отрицательным");
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }
    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("неккоректная сумма внесения");

        }
        balance += amount;
        cout << "средства успешно внесены. остаток на счете: " << balance << endl;
    }
    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("некорректная сумма снятия");
        }
        if (amount > balance) {
            throw invalid_argument("недостаточно средств на счете");
        }
        balance -= amount;
        cout << "средства успешно сняты. остаток на счете: " << balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    double getInterest() const {
        return balance * interestRate * (1.0 / 12);
    }
    void setInterestRate(double rate) {
        if (rate < 0) {
            throw invalid_argument("некорректная процентная ставка");
        }
        this->interestRate = rate;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
    static bool transfer(BankAccount& from, BankAccount& to, double amount) {
        if (amount <= 0) {
            throw invalid_argument("некорректная сумма перевода");
        }
        if (amount > from.balance) {
            throw invalid_argument("недостаточно средств для перевода");
        }
        from.balance -= amount;
        to.balance += amount;
        cout << "перевод успешно выполнен" << endl;
        return true;
    }

};
int main() {
    SetConsoleOutputCP(1251);

    try {
        BankAccount acc1(12345, 1000);
        BankAccount acc2(54321, 500);
        double depositAmount;
        cout << "Введите сумму для внесения на счет 1: ";
        cin >> depositAmount;
        acc1.deposit(depositAmount);
        double withdrawAmount;
        cout << "Введите сумму для снятия со счета 1: ";
        cin >> withdrawAmount;
        acc1.withdraw(withdrawAmount);
        cout << "Баланс счета 1: " << acc1.getBalance() << endl;
        double interestRate;
        cout << "Введите процентную ставку: ";
        cin >> interestRate;
        acc1.setInterestRate(interestRate);
        cout << "Проценты за текущий месяц: " << acc1.getInterest() << endl;
        double transferAmount;
        cout << "Введите сумму для перевода со счета 1 на счет 2: ";
        cin >> transferAmount;
        BankAccount::transfer(acc1, acc2, transferAmount);
        cout << "Номер счета 1: " << acc1.getAccountNumber() << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
};