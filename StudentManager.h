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
    void displaySearchMenu();
    void displaySortingMenu();
  
    bool isExistingId(const string& id);
    void searchByName(const string& name);
    void searchByStudentID(const string& id);
    void searchByAdmissionYear(const string& year);
    void searchByBirthYear(const string& year);
    void searchByDepartment(const string& department);

    void sortById();
    void sortByName();
    void sortByBirthYear();
    void sortByDepartment();

    ~StudentManager();
};

#endif
