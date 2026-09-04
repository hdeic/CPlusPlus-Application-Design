#include <iostream>
#include <string>

using namespace std;

int main() {
    // Step 1: Understanding cout and cin
    cout << "Welcome to my application!" << endl;

    // Assignment & Step 6: Create at least six variables related to your application
    // Using at least four different C++ data types (string, double, int, char, bool)
    string userName = "Alex";                               // User's name (string)
    string appName = "Student Record Management System";    // Application name (string)
    double versionNumber = 1.0;                             // Version number (double)
    int studentID = 1001;                                   // Student ID (int)
    double studentGPA = 3.85;                               // Student GPA (double)
    char letterGrade = 'A';                                 // Letter grade (char)
    bool accountActive = true;                              // Account active condition (bool)
    int totalRecords = 250;                                 // Total records count (int)

    // Optional cin: allow user to customize their name
    cout << "\nPlease enter your name (press enter for default): ";
    string inputName;
    getline(cin, inputName);
    if (!inputName.empty()) {
        userName = inputName;
    }

    // Clean Welcome Screen displaying all variables
    cout << "\n==========================================" << endl;
    cout << "      WELCOME TO " << appName << endl;
    cout << "==========================================" << endl;
    cout << "User Name:        " << userName << endl;
    cout << "Application Name: " << appName << endl;
    cout << "Version Number:   " << versionNumber << endl;
    cout << "Student ID:       " << studentID << endl;
    cout << "Student GPA:      " << studentGPA << endl;
    cout << "Letter Grade:     " << letterGrade << endl;
    cout << "Account Active:   " << (accountActive ? "true" : "false") << endl;
    cout << "Total Records:    " << totalRecords << endl;
    cout << "==========================================" << endl;
    cout << "Hello, " << userName << "! Your workspace is ready." << endl;

    // Step 2: Build the Console Interface with cout
    cout << "\n=== MY APPLICATION ===" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Search" << endl;
    cout << "4. Exit" << endl;

    // Step 1: Introducing cin
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice;
    cout << "You selected option: " << choice << endl;

    return 0;
}
