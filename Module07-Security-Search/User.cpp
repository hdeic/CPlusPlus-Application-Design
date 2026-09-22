#include <iostream>
#include "User.h"

using namespace std;

User::User(const string &name) : username(name) {}

string User::getUsername() const {
    return username;
}

bool User::canModifyRecords() const {
    return false;
}

void User::denyAccess(const string &action) const {
    cout << "  [" << getRole() << " " << username << "] " << action
         << " -> ACCESS DENIED (only an Admin can " << action << " records)\n";
}

void User::viewRecords(const Inventory &inventory) const {
    cout << "  [" << getRole() << " " << username << "] view records -> allowed\n";
    inventory.displayAll();
}

void User::searchRecord(const Inventory &inventory, int productId) const {
    cout << "  [" << getRole() << " " << username << "] binary search for product ID "
         << productId << " -> allowed\n";
    int comparisons = 0;
    const Product *found = inventory.findById(productId, comparisons, true);
    if (found != nullptr) {
        cout << "    FOUND in " << comparisons << " comparison(s) out of "
             << inventory.size() << " records:\n";
        found->displayDetails();
    } else {
        cout << "    NOT FOUND after " << comparisons << " comparison(s).\n";
    }
}

bool User::addRecord(Inventory &, const Product &) {
    denyAccess("add");
    return false;
}

bool User::deleteRecord(Inventory &, int) {
    denyAccess("delete");
    return false;
}

Admin::Admin(const string &name) : User(name) {}

string Admin::getRole() const {
    return "Admin";
}

bool Admin::canModifyRecords() const {
    return true;
}

bool Admin::addRecord(Inventory &inventory, const Product &product) {
    int position = inventory.addSorted(product);
    cout << "  [" << getRole() << " " << username << "] add ID " << product.getProductId()
         << " (" << product.getDescription() << ")";
    if (position == -1) {
        cout << " -> rejected, product ID already exists\n";
        return false;
    }
    cout << " -> inserted at sorted position " << position << "\n";
    return true;
}

bool Admin::deleteRecord(Inventory &inventory, int productId) {
    bool removed = inventory.removeById(productId);
    cout << "  [" << getRole() << " " << username << "] delete ID " << productId
         << (removed ? " -> deleted\n" : " -> rejected, product ID not found\n");
    return removed;
}

RegularUser::RegularUser(const string &name) : User(name) {}

string RegularUser::getRole() const {
    return "Regular User";
}
