#include "StudentManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#define STUDENT_LIST_SIZE 100

using namespace std;

StudentManager::StudentManager(string filepath) :student_count(0) {
    fstream repo;
    repo.open(filepath, ios::in);
    if (!repo.is_open()) {
        cout<< "File does not exist. Attempting to create new ..." << endl;
        repo.open(filepath, ios::out);
        if (!repo.is_open()) {
            cerr << "Unable to create file. Check permissions." << endl;
        } else {
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
    string name;
    int id;
    int birth_year;
    string department;
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
        if (tel.length() > 12) 
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

void StudentManager::printAll() {
    for(int i=0; i<student_count; i++) {
        student_list[i].print();
    }
}

void StudentManager::displayMenu() {
    while(true) {
        cout << "\n- Main Menu" << endl;
        cout << "1. Insertion" << endl;
        cout << "2. Search" << endl;
        cout << "3. Sorting Option" << endl;
        cout << "4. Exit" << endl;
        cout << "> ";
        char choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1':
                addStudent();
                break;
            case '2':
                cout << "Search function not implemented yet." << endl;
                break;
            case '3':
                displaySortingMenu();
                break;
            case '4':
                cout << "Exiting program." << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}

void StudentManager::displaySortingMenu() {
    cout << "\n- Sorting Options" << endl;
    cout << "1. Sort by Name" << endl;
    cout << "2. Sort by Student ID" << endl;
    cout << "3. Sort by Birth Year" << endl;
    cout << "4. Sort by Department name" << endl;
    cout << "> ";

    char choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case '1':
            sortByName();
            break;
        case '2':
            sortById();
            break;
        case '3':
            sortByBirthYear();
            break;
        case '4':
            sortByDepartment();
            break;
        default:
            cout << "Invalid option. Returning to main menu." << endl;
            return;
    }
    cout << "Sorting complete. Returning to main menu." << endl;
}

void StudentManager::sortById() {
    sort(student_list, student_list + student_count, [](const Student& a, const Student& b) {
        return a.getId() < b.getId();
    });
    cout << "Sorted by Student ID." << endl;
    printAll();
}

void StudentManager::sortByName() {
    sort(student_list, student_list + student_count, [](const Student& a, const Student& b) {
        return a.getName() < b.getName();
    });
    cout << "Sorted by Name." << endl;
    printAll();
}

void StudentManager::sortByBirthYear() {
    sort(student_list, student_list + student_count, [](const Student& a, const Student& b) {
        return a.getBirthYear() < b.getBirthYear();
    });
    cout << "Sorted by Birth Year." << endl;
    printAll();
}

void StudentManager::sortByDepartment() {
    sort(student_list, student_list + student_count, [](const Student& a, const Student& b) {
        return a.getDepartment() < b.getDepartment();
    });
    cout << "Sorted by Department." << endl;
    printAll();
}

StudentManager::~StudentManager() {
    delete[] student_list;
}
