#include <iostream>
#include <string>
#include <limits>

using namespace std;

void addRecord() {
    cout << "Add Record selected." << endl;
}

void viewRecords() {
    cout << "View Records selected." << endl;
}

void searchRecords() {
    cout << "Search selected." << endl;
}

void updateRecord() {
    cout << "Update Record selected." << endl;
}

void deleteRecord() {
    cout << "Delete Record selected." << endl;
}

int main() {
    int choice = 0;

    // Loop continues until the user chooses Exit (option 6)
    while (choice != 6) {
        cout << "\n=== MY APPLICATION ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        cin >> choice;

        // Input validation: ensure invalid input does not crash the program or loop infinitely
        if (cin.fail()) {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad characters
            cout << "Invalid input. Please enter a number." << endl;
            continue;                                            // Re-prompt
        }

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                searchRecords();
                break;
            case 4:
                updateRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
