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
    void printAll() const;
    void displayMenu();
    void displaySearchMenu() const;
    void displaySortingMenu() const;
  
    bool isExistingId(const string& id) const;
    void searchByName(const string& name) const;
    void searchByStudentID(const string& id) const;
    void searchByAdmissionYear(const string& year) const;
    void searchByBirthYear(const string& year) const;
    void searchByDepartment(const string& department) const;

    void sortById() const;
    void sortByName() const;
    void sortByBirthYear() const;
    void sortByDepartment() const;

    ~StudentManager();
};

#endif
