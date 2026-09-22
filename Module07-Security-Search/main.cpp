#include <iostream>
#include <iomanip>
#include "Inventory.h"
#include "User.h"

using namespace std;

void printSection(const string &title) {
    cout << "\n================================================================================\n";
    cout << "  " << title << "\n";
    cout << "================================================================================\n";
}

void printPermissions(const User &user) {
    string modify = user.canModifyRecords() ? "yes" : "no";
    cout << "  " << left << setw(14) << user.getRole()
         << setw(18) << user.getUsername()
         << setw(7) << "yes" << setw(9) << "yes"
         << setw(6) << modify << modify << "\n";
}

int main() {
    Inventory store;
    Admin admin("store_admin");
    RegularUser shopper("shopper_01");
    User *users[] = {&shopper, &admin};

    printSection("Product Inventory System - Roles, Permissions & Binary Search");
    cout << "  " << left << setw(14) << "ROLE" << setw(18) << "USERNAME"
         << setw(7) << "VIEW" << setw(9) << "SEARCH" << setw(6) << "ADD" << "DELETE" << "\n";
    for (User *user : users) {
        printPermissions(*user);
    }

    printSection("1. Admin adds records in random ID order; the list stays sorted");
    admin.addRecord(store, Product(276, "84029E", "RED WOOLLY HOTTIE WHITE HEART.", 6, 3.39));
    admin.addRecord(store, Product(105, "71053", "WHITE METAL LANTERN", 6, 3.39));
    admin.addRecord(store, Product(342, "84406B", "CREAM CUPID HEARTS COAT HANGER", 8, 2.75));
    admin.addRecord(store, Product(150, "22752", "SET 7 BABUSHKA NESTING BOXES", 2, 7.65));
    admin.addRecord(store, Product(201, "85123A", "WHITE HANGING HEART T-LIGHT HOLDER", 6, 2.55));
    admin.addRecord(store, Product(118, "84029G", "KNITTED UNION FLAG HOT WATER BOTTLE", 6, 3.39));
    admin.addRecord(store, Product(389, "84879", "ASSORTED COLOUR BIRD ORNAMENT", 32, 1.69));
    admin.viewRecords(store);

    printSection("2. Same add request from each role (restricted by role)");
    for (User *user : users) {
        user->addRecord(store, Product(233, "22633", "HAND WARMER UNION JACK", 6, 1.85));
    }

    printSection("3. Regular User views records");
    shopper.viewRecords(store);

    printSection("4. Regular User runs a binary search by product ID");
    shopper.searchRecord(store, 276);
    cout << "\n";
    shopper.searchRecord(store, 999);

    printSection("5. Same delete request from each role (restricted by role)");
    for (User *user : users) {
        user->deleteRecord(store, 150);
    }
    admin.deleteRecord(store, 150);

    printSection("6. Admin confirms the delete with a binary search");
    admin.searchRecord(store, 150);
    cout << "\n";
    admin.addRecord(store, Product(105, "71053", "WHITE METAL LANTERN", 6, 3.39));

    printSection("7. Final inventory");
    admin.viewRecords(store);
    cout << fixed << setprecision(2);
    cout << "\n  Total inventory value: $" << store.totalStockValue() << "\n";

    return 0;
}
