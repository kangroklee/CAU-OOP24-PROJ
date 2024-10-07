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

//searching(황병윤)
StudentManager::~StudentManager() {};

void StudentManager::displaySearchMenu() {
    std::cout << "- Search -" << std::endl;
    std::cout << "1. Search by name" << std::endl;
    std::cout << "2. Search by student ID (10 digits)" << std::endl;
    std::cout << "3. Search by admission year (4 digits)" << std::endl;
    std::cout << "4. Search by birth year (4 digits)" << std::endl;
    std::cout << "5. Search by department name" << std::endl;
    std::cout << "6. List All" << std::endl;
    std::cout << "> ";
}


void StudentManager::searchByName(const std::string& name) {
    bool found = false;
    Student* current = student_list;  // Assuming student_list is the head pointer of the linked list
    
    while (current != nullptr) {
        if (current->getName() == name) {
            current->display();
            found = true;
            break;  // If you want to stop after finding the first match
        }
        current++;  // Assuming there is a method to get the next student in the list
    }

    if (!found) {
        std::cout << "No student found with name: " << name << std::endl;
    }
}


void StudentManager::searchByStudentID(const std::string& id) {
    int idcopy = std::stoi(id);
    bool found = false;
    Student* current = student_list;

    while (current != nullptr) {
        if (current->getId() == idcopy) {
            current->display();
            found = true;
            break;
        }
        current++;  // Assuming you have a method or pointer to the next student in the list
    }

    if (!found) {
        std::cout << "No student found with ID: " << id << std::endl;
    }
}


void StudentManager::searchByAdmissionYear(const std::string& year) {
    bool found = false;
    Student* current = student_list;

    for (int i = 0; i < STUDENT_LIST_SIZE; ++i) {
        std::stringstream ss;
        ss << current->getId();
        std::string idStr = ss.str();
        std::string idFirstFour = idStr.substr(0, 4);

        if (idFirstFour == year) {
            current->display();
            found = true;
        }
        current++;
    }

    if (!found) {
        std::cout << "No student found admitted in year: " << year << std::endl;
    }
}


void StudentManager::searchByBirthYear(const std::string& year) {
    int yearcopy = std::stoi(year);
    bool found = false;

    for (int i = 0; i < STUDENT_LIST_SIZE; ++i) {
        if (student_list[i].getBirthYear() == yearcopy) {
            student_list[i].display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No student found born in year: " << year << std::endl;
    }
}

void StudentManager::searchByDepartment(const std::string& department) {
    bool found = false;

    for (int i = 0; i < STUDENT_LIST_SIZE; ++i) {
        if (student_list[i].getDepartment().find(department) != std::string::npos) {
            student_list[i].display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No student found in department: " << department << std::endl;
    }
}


void StudentManager::listAll(){
    std::cout << "not made yet";
}
