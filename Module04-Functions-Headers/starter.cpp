#include <iostream>
using namespace std;

int main() {
    string names[3] = {"Ada", "Sam", "Jordan"};
    int scores[3] = {91, 84, 97};

    int *scorePtr = &scores[0];

    for (int i = 0; i < 3; i++) {
        cout << names[i] << ": " << scores[i] << endl;
    }

    cout << "First score through pointer: " << *scorePtr << endl;
    return 0;
}
