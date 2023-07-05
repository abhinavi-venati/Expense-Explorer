#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

struct Transaction {
    string category;
    double amount;
};

vector<Transaction> transactions;
double savingsGoal = 0.0;

void addTransaction(const string& category, double amount) {
    Transaction transaction;
    transaction.category = category;
    transaction.amount = amount;
    transactions.push_back(transaction);
}

void displayTransactions() {
    cout << "Category\tAmount" << endl;
    for (const auto& transaction : transactions) {
        cout << transaction.category << "\t\t" << transaction.amount << endl;
    }
}

double calculateTotalExpense() {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        if (transaction.amount < 0) {
            total += transaction.amount;
        }
    }
    return total;
}

double calculateTotalIncome() {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        if (transaction.amount > 0) {
            total += transaction.amount;
        }
    }
    return total;
}

double calculateExpenseByCategory(const string& category) {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        if (transaction.category == category && transaction.amount < 0) {
            total += transaction.amount;
        }
    }
    return total;
}

void setSavingsGoal(double goal) {
    savingsGoal = goal;
}

double calculateSavingsProgress() {
    double savingsAchieved = calculateTotalIncome() - abs(calculateTotalExpense());
    double progress = (savingsAchieved / savingsGoal) * 100.0;

    return progress;
}

string findHighestExpenseCategory() {
    string highestCategory;
    double highestExpense = numeric_limits<double>::lowest();

    vector<string> expenseCategories = {"Rent", "Food", "Entertainment", "Medical"};
    for (const auto& category : expenseCategories) {
        double totalExpense = calculateExpenseByCategory(category);
        if (totalExpense < highestExpense) {
            highestExpense = totalExpense;
            highestCategory = category;
        }
    }
    return highestCategory;
}

int main() {
    cout << "*** Personal Finance Tracker ***" << endl;

    while (true) {
        cout << "Enter 'income' or 'expense' or 'goal' (or 'quit' to exit): ";
        string choice;
        cin >> choice;

        if (choice == "quit") {
            break;
        }

        if (choice == "income") {
            cout << "Enter income amount: ";
            double amount;
            cin >> amount;
            addTransaction("Income", amount);
        }
        else if (choice == "expense") {
            cout << "Enter expense category: ";
            string category;
            cin >> category;

            cout << "Enter expense amount: ";
            double amount;
            cin >> amount;

            addTransaction(category, -amount);
        }
        else if (choice == "goal") {
            cout << "Enter savings goal amount: ";
            double goal;
            cin >> goal;
            setSavingsGoal(goal);
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Recorded successfully!" << endl << endl;
    }

    cout << "All Transactions:" << endl;
    displayTransactions();

    cout << endl << "Expense Summary:" << endl;
    cout << "Category\tAmount" << endl;
    cout << "---------\t------" << endl;

    vector<string> expenseCategories = {"Rent", "Food", "Entertainment", "Medical"};
    for (const auto& category : expenseCategories) {
        double totalExpense = calculateExpenseByCategory(category);
        cout << category << "\t\t" << totalExpense << endl;
    }

    double totalExpense = calculateTotalExpense();
    cout << "Total Expense: " << totalExpense << endl;

    double totalIncome = calculateTotalIncome();
    cout << "Total Income: " << totalIncome << endl;

    if (!transactions.empty()) {
        string highestExpenseCategory = findHighestExpenseCategory();
        cout << "The highest expense category is: " << highestExpenseCategory << endl;
    }

    double finalAmount = totalIncome + totalExpense;
    cout << "Final Amount: " << finalAmount << endl;

    if (savingsGoal > 0) {
        double savingsProgress = calculateSavingsProgress();
        double savingsAchieved = calculateTotalIncome() - abs(calculateTotalExpense());

        cout << "Savings Goal Progress: " << savingsProgress << "%" << endl;
        cout << "Savings Achieved: " << savingsAchieved << endl;
    }

    return 0;
}
