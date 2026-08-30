#include <iostream>
#include <limits>

using namespace std;

int main() {
    int yearOfBirth = 1995;
    char gender = 'f';
    bool isOlderThan18 = true;
    float averageGrade = 4.5f;
    double balance = 45678945856.0;

    cout << "Size of int is " << sizeof(int) << " bytes\n";
    cout << "Int min value is " << numeric_limits<int>::min() << "\n";
    cout << "Int max value is " << numeric_limits<int>::max() << "\n";

    cout << "Size of unsigned int is " << sizeof(unsigned int) << " bytes\n";
    cout << "UInt max value is " << numeric_limits<unsigned int>::max() << "\n";

    unsigned int u = numeric_limits<unsigned int>::max();
    cout << "Unsigned int before overflow: " << u << "\n";
    u = u + 1u;
    cout << "Unsigned int after overflow (u+1): " << u << "\n";

    cout << "yearOfBirth = " << yearOfBirth << "\n";
    cout << "gender = " << gender << "\n";
    cout << "isOlderThan18 = " << (isOlderThan18 ? "true" : "false") << "\n";
    cout << "averageGrade = " << averageGrade << "\n";
    cout << "balance = " << balance << "\n";

    return 0;
}
