#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    double score;

public:
    Student(string studentName, int studentId, double studentScore) {
        name = studentName;
        id = studentId;
        score = studentScore;
    }

    void displayStudent() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Score: " << score << endl;
    }

    string getName() {
        return name;
    }

    void setScore(double newScore) {
        score = newScore;
    }
};

int main() {
    Student student1("Jordan", 101, 92.5);
    Student student2("Taylor", 102, 87.0);

    student1.displayStudent();
    cout << endl;
    student2.displayStudent();

    return 0;
}
