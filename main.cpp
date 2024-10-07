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

    //searching(황병윤)
    sm.displaySearchMenu();
    
    int choice;
    std::string input;

    while (true) {
        
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter student name: ";
                std::cin >> input;
                sm.searchByName(input);  // Call StudentManager's searchByName
                break;
            case 2:
                std::cout << "Enter student ID: ";
                std::cin >> input;
                sm.searchByStudentID(input);  // Call StudentManager's searchByStudentID
                break;
            case 3:
                std::cout << "Enter admission year: ";
                std::cin >> input;
                sm.searchByAdmissionYear(input);  // Call StudentManager's searchByAdmissionYear
                break;
            case 4:
                std::cout << "Enter birth year: ";
                std::cin >> input;
                sm.searchByBirthYear(input);  // Call StudentManager's searchByBirthYear
                break;
            case 5:
                std::cout << "Department name keyword? ";
                std::cin >> input;
                sm.searchByDepartment(input);  // Call StudentManager's searchByDepartment
                break;
            case 6:
                sm.listAll();  // Call StudentManager's listAll
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
