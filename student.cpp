#include <iostream>
#include <vector>   
#include <string>   

// Define a structure named 'Student' to hold student information.
struct Student {
    int id;            
    std::string name;   
    int age;         
    std::string major;  
};

// Function to display the details of a single student.
void displayStudent(const Student& s) {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "ID: " << s.id << std::endl;
    std::cout << "Name: " << s.name << std::endl;
    std::cout << "Age: " << s.age << std::endl;
    std::cout << "Major: " << s.major << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

// Function to add a new student record to the vector of students.
void addStudent(std::vector<Student>& students) {
    Student newStudent; 

    std::cout << "\nEnter Student ID: ";
    std::cin >> newStudent.id;
    std::cin.ignore(); 

    std::cout << "Enter Student Name: ";
    std::getline(std::cin, newStudent.name);

    std::cout << "Enter Student Age: ";
    std::cin >> newStudent.age;
    std::cin.ignore();

    std::cout << "Enter Student Major: ";
    std::getline(std::cin, newStudent.major);

    students.push_back(newStudent); 
    std::cout << "\nStudent added successfully!" << std::endl;
}

void viewAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "\nNo students to display." << std::endl;
        return;
    }
    std::cout << "\n--- All Students ---" << std::endl;
    for (const auto& s : students) { 
        displayStudent(s);      
    }
    std::cout << "----------------------" << std::endl;
}

// Function to search for a student by ID.
Student* findStudentById(std::vector<Student>& students, int id) {
    for (auto& s : students) {
        if (s.id == id) {
            return &s;   
        }
    }
    return nullptr;
}

int main() {
    std::vector<Student> students; 
    int choice;                   

    do {
        std::cout << "\n--- Student Management System ---" << std::endl;
        std::cout << "1. Add New Student" << std::endl;
        std::cout << "2. View All Students" << std::endl;
        std::cout << "3. Search Student by ID" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice; 

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewAllStudents(students);
                break;
            case 3: {
                int searchId;
                std::cout << "Enter Student ID to search: ";
                std::cin >> searchId;
                Student* foundStudent = findStudentById(students, searchId);
                if (foundStudent) {
                    std::cout << "\nStudent Found:" << std::endl;
                    displayStudent(*foundStudent); 
                } else {
                    std::cout << "\nStudent with ID " << searchId << " not found." << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "\nExiting Student Management System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 4);

    return 0; 
}
