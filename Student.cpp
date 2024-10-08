#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student() {}

Student::Student(const string& name, const int id, const int birth_year, const string& department, const string& tel) 
    : name(name), id(id), birth_year(birth_year), department(department), tel(tel) { }

void Student::print() const {
    cout<< name << " " 
        << id << " "
        << birth_year << " "
        << department << " "
        << tel << " " << endl;
}

string Student::toString() const {
    return name+","+to_string(id)+","+to_string(birth_year)+","+department+","+tel+"\n";
}

string Student::getName() const {
    return name;
}

int Student::getId() const {
    return id;
}

int Student::getBirthYear() const {
    return birth_year;
}

string Student::getDepartment() const {
    return department;
}

string Student::getTel() const {
    return tel;
}

