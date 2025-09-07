#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

string getCurrentDateTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

bool checkPassword() {
    string input;
    string password = "diary123"; // You can change this
    cout << "Enter password to access your diary: ";
    cin >> input;
    return input == password;
}

void addEntry() {
    ofstream file("diary.txt", ios::app);
    if (!file) {
        cout << "Error opening diary file.\n";
        return;
    }

    cin.ignore(); // clear input buffer
    string entry;
    cout << "Write your diary entry:\n> ";
    getline(cin, entry);

    string datetime = getCurrentDateTime();
    file << "[" << datetime << "] " << entry << "\n";
    file.close();

    cout << "✅ Entry saved!\n";
}

void viewEntries() {
    ifstream file("diary.txt");
    if (!file) {
        cout << "No diary entries found.\n";
        return;
    }

    string line;
    cout << "\n📘 Your Diary Entries:\n";
    cout << "--------------------------\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void searchEntries() {
    ifstream file("diary.txt");
    if (!file) {
        cout << "No diary entries to search.\n";
        return;
    }

    string keyword;
    cout << "Enter keyword to search: ";
    cin.ignore();
    getline(cin, keyword);

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "🔍 " << line << "\n";
            found = true;
        }
    }

    if (!found) cout << "No entries matched your search.\n";

    file.close();
}

int main() {
    if (!checkPassword()) {
        cout << "❌ Incorrect password. Exiting...\n";
        return 1;
    }

    int choice;
    do {
        cout << "\n=== Personal Diary Menu ===\n";
        cout << "1. Add New Entry\n";
        cout << "2. View All Entries\n";
        cout << "3. Search Entries\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addEntry(); break;
            case 2: viewEntries(); break;
            case 3: searchEntries(); break;
            case 4: cout << "👋 Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
