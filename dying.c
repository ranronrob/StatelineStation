#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define the maximum number of students
#define MAX_STUDENTS 5

// Define the struct for student data
typedef struct {
    int id;
    char dob[11]; // Assuming the format is YYYY-MM-DD
    char first_name[30];
    char last_name[30];
    char student_class[10];
    float phonics_score;
    float reading_score;
    float maths_score;
    float average_score;
} Student;

// Declare an array of structs to hold student records
Student students[MAX_STUDENTS];
int num_students = 0; // Current number of students

// Function prototypes
void addStudentRecord();
void calculateStudentAverage();
void printStudentReport();
void printMenu();
bool isFull();
bool idExists(int id);
void calculateAverage(Student *student);
void printReportForStudent(int student_id);

// Main function
int main() {
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                if(!isFull()) {
                    addStudentRecord();
                } else {
                    printf("The student records are full.\n");
                }
                break;
            case 2:
                calculateStudentAverage();
                break;
            case 3:
                printStudentReport();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
                break;
        }
    } while(choice != 4);
    return 0;
}

// Function to print the main menu
void printMenu() {
    printf("\n--- Student Record System Menu ---\n");
    printf("1. Add Student Record\n");
    printf("2. Calculate Student Average\n");
    printf("3. Print Student Report\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Helper function to check if the array is full
bool isFull() {
    return num_students >= MAX_STUDENTS;
}

// Helper function to check if a student ID already exists
bool idExists(int id) {
    for(int i = 0; i < num_students; ++i) {
        if(students[i].id == id) {
            return true;
        }
    }
    return false;
}

// Function to add a student record
void addStudentRecord() {
    // This will hold the new student record
    Student new_student;
    
    // Prompt for input and add record
    printf("Enter student ID: ");
    scanf("%d", &new_student.id);
    
    // Check for unique student ID
    if(idExists(new_student.id)) {
        printf("A student with this ID already exists.\n");
        return;
    }
    
    printf("Enter date of birth (YYYY-MM-DD): ");
    scanf("%10s", new_student.dob);
    printf("Enter first name: ");
    scanf("%29s", new_student.first_name);
    printf("Enter last name: ");
    scanf("%29s", new_student.last_name);
    printf("Enter class: ");
    scanf("%9s", new_student.student_class);
    
    // Add the new student to the array and increment the counter
    students[num_students++] = new_student;
    printf("Student record added successfully!\n");
}

// Function to calculate student averages
void calculateStudentAverage() {
    for(int i = 0; i < num_students; ++i) {
        calculateAverage(&students[i]);
    }
    printf("Student averages calculated.\n");
}

// Helper function to calculate the average score for a student
void calculateAverage(Student *student) {
    if(student) {
        (*student).average_score = ((*student).phonics_score + (*student).reading_score + (*student).maths_score) / 3;
    }
}

// Function to print student report
void printStudentReport() {
    int student_id;
    printf("Enter student ID for the report: ");
    scanf("%d", &student_id);
    printReportForStudent(student_id);
}

// Helper function to print the report for a specific student
void printReportForStudent(int student_id) {
    for(int i = 0; i < num_students; ++i) {
        if(students[i].id == student_id) {
            printf("\n--- Student Report ---\n");
            printf("ID: %d\n", students[i].id);
            printf("First Name: %s\n", students[i].first_name);
            printf("Last Name: %s\n", students[i].last_name);
            printf("Phonics Score: %.2f\n", students[i].phonics_score);
            printf("Reading Score: %.2f\n", students[i].reading_score);
            printf("Maths Score: %.2f\n", students[i].maths_score);
            printf("Average Score: %.2f\n", students[i].average_score);
            return;
        }
    }
    printf("No student found with ID %d.\n", student_id);
}