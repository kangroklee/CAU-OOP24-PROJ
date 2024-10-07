#ifndef __STUDENT_MANAGER_H__
#define __STUDENT_MANAGER_H__

#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

class StudentManager {
private: 
    int student_count;
    Student* student_list;
    string filepath;


public:
    StudentManager(string filepath);
    void addStudent();
    void printAll();
    void displayMenu();
    ~StudentManager();
    //searching(황병윤)
    void displaySearchMenu();

    void searchByName(const std::string& name);
    void searchByStudentID(const std::string& id);
    void searchByAdmissionYear(const std::string& year);
    void searchByBirthYear(const std::string& year);
    void searchByDepartment(const std::string& department);
    void listAll();  
};

#endif
#endif
