#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
public:
    User(string name) : username(name) {}
};

class Admin : public User {
public:
    Admin(string name) : User(name) {}
    void addRecord() { cout << username << " added a record" << endl; }
    void deleteRecord() { cout << username << " deleted a record" << endl; }
};

int binarySearch(int data[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (data[mid] == target) return mid;
        if (data[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    Admin admin("admin");
    admin.addRecord();
    admin.deleteRecord();

    int ids[] = {101, 105, 118, 150, 201, 276};
    int size = sizeof(ids) / sizeof(ids[0]);
    cout << "Index of 150: " << binarySearch(ids, size, 150) << endl;
    cout << "Index of 999: " << binarySearch(ids, size, 999) << endl;

    return 0;
}
