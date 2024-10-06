#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <iostream>
#include <string>
using namespace std;

class Student {
private: 
    string name; //up to 15 chars
    int id; //exactly 10 digits
    int birth_year; // exactly 4 digits
    string department; // may contain space
    string tel;

public:
    Student();
    Student(const string& name, const int id, const int birth_year, const string& department, const string& tel);

    void print() const;
    string toString() const;

    string getName() const;
    int getId() const;
    int getBirthYear() const;
    string getDepartment() const;
    string getTel() const;

    //setters 생략

    ~Student() {}
};

#endif
