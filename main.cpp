#include <iostream>
#include "Student.h"
#include "StudentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Check args: need path to student file" <<endl;
        return -1;
    }
    string filepath = argv[1];
    StudentManager sm = StudentManager(filepath);

    sm.printAll();
    sm.addStudent();
    sm.printAll();
    return 0;
}