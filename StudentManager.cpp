#include "StudentManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define STUDENT_LIST_SIZE 100

using namespace std;

StudentManager::StudentManager(string filepath) :student_count(0) {
    fstream repo;
    repo.open(filepath, ios::in);
    if (!repo.is_open()) { // 파일 존재 x
        cout<< "File does not exist. Attempting to create new ..." << endl;
        repo.open(filepath, ios::out);
        if (!repo.is_open()) {
            cerr << "Unable to create file. Check permissions." << endl;
        } else { // 파일 생성 성공
            cout<< "New file " << filepath << " created." << endl; 
            this->filepath = filepath;
            repo.close();
        }
    } else {
        cout << "File opened successfully." << endl;
        string line;
        student_list = new Student[STUDENT_LIST_SIZE]; 

        repo.seekg(0, ios::beg);
        while(getline(repo, line)) { 
            // 파싱 (이름,학번,출생연도,학과명,전화번호)
            stringstream ss(line);
            string name, dept, tel;
            int id, birth_year;

            getline(ss, name, ',');
            ss >> id;
            ss.ignore(1);
            ss >> birth_year;
            ss.ignore(1);
            getline(ss, dept, ',');
            getline(ss, tel, ',');

            student_list[student_count] = Student(name, id, birth_year, dept, tel);
            student_count++;
        }
        this->filepath = filepath;
        repo.close();
    }
}

void StudentManager::addStudent() {
    string name; //up to 15 chars
    int id; //exactly 10 digits
    int birth_year; // exactly 4 digits
    string department; // may contain space
    string tel;

    while(true) {
        cout << "Name: ";
        cin >> name;
        if (name.length() > 15) 
            cerr << "Name cannot exceed 15 characters.";
        else 
            break;
    }
    
    while(true) {
        cout << "Student ID: ";
        cin >> id;
        if (to_string(id).length() != 10) 
            cerr << "ID must be 10 digits";
        else 
            break;
    }

    while(true) {
        cout << "Birth Year: ";
        cin >> birth_year;
        if (to_string(birth_year).length() != 4) 
            cerr << "Birth year must be 4 digits";
        else 
            break;
    }

    cout << "Department: ";
    cin.ignore();
    getline(cin, department);

    while(true) {
        cout << "Tel: ";
        cin >> tel;
        if (name.length() > 12) 
            cerr << "Tel. cannot exceed 12 characters.";
        else 
            break;
    }

    fstream repo;
    repo.open(filepath, ios::out | ios::app);
    if(!repo.is_open()) {
        cerr<< "File missing. Unable to add student." <<endl;
        return;
    }

    Student s = Student(name, id, birth_year, department, tel);
    repo << s.toString();
    repo.close();
    student_list[student_count] = s;
    student_count++;
    cout << "Successfully added new student." << endl;
}

void StudentManager::printAll() { // 요구사항 형식에 맞게 추후 수정
    for(int i=0; i<student_count; i++) {
        student_list[i].print();
    }
}

void StudentManager::displayMenu() {
    while(true) {
        cout << "1. Insertion" << endl;
        cout << "2. Search" << endl;
        cout << "3. Sorting Option" << endl;
        cout << "4. Exit" << endl;
        cout << ">> ";
        char choice = getchar();

        switch (choice) {
            case 1:
                addStudent();
                continue;
            case 4:
                break;
            default:
                continue;
        }
        while (getchar() != '\n');
    }
}

StudentManager::~StudentManager() {};
