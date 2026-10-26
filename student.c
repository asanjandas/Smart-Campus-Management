#include <stdio.h>
#include <string.h>
#include "student.h"
#include "file_utils.h"

#define STUDENT_FILE "data/students.txt"

void student_menu() {
    int choice;
    do {
        printf("\n--- Student Management ---\n");
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        choice = get_int();

        switch(choice) {
            case 1: add_student(); break;
            case 2: display_students(); break;
            case 3: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
}

int check_duplicate_id(int id) {
    FILE *file = fopen(STUDENT_FILE, "r");
    if (file == NULL) return 0; // File doesn't exist yet, so no duplicates

    Student temp;
    // Read formatted data separated by pipes
    while (fscanf(file, "%d|%49[^|]|%29[^|]|%d|%14[^\n]\n", 
           &temp.id, temp.name, temp.department, &temp.semester, temp.phone) != EOF) {
        if (temp.id == id) {
            fclose(file);
            return 1; // Duplicate found
        }
    }
    fclose(file);
    return 0; // No duplicate
}

void add_student() {
    Student s;
    printf("\nEnter Student ID: ");
    s.id = get_int();

    if (check_duplicate_id(s.id)) {
        printf("Error: Student ID %d already exists!\n", s.id);
        return;
    }

    printf("Enter Name: ");
    get_string(s.name, sizeof(s.name));
    
    printf("Enter Department: ");
    get_string(s.department, sizeof(s.department));
    
    printf("Enter Semester: ");
    s.semester = get_int();
    
    printf("Enter Phone Number: ");
    get_string(s.phone, sizeof(s.phone));

    // Open in append mode ("a") to add to the end of the file
    FILE *file = fopen(STUDENT_FILE, "a");
    if (file == NULL) {
        printf("Error: Could not open file to save data.\n");
        return;
    }

    // Save with pipe (|) delimiters for easy reading later
    fprintf(file, "%d|%s|%s|%d|%s\n", s.id, s.name, s.department, s.semester, s.phone);
    fclose(file);
    printf("Student added successfully!\n");
}

void display_students() {
    FILE *file = fopen(STUDENT_FILE, "r");
    if (file == NULL) {
        printf("\nNo student records found. (File is empty or missing)\n");
        return;
    }

    Student s;
    printf("\n%-10s | %-20s | %-15s | %-8s | %-15s\n", "ID", "Name", "Department", "Semester", "Phone");
    printf("--------------------------------------------------------------------------------------\n");
    
    int count = 0;
    while (fscanf(file, "%d|%49[^|]|%29[^|]|%d|%14[^\n]\n", 
           &s.id, s.name, s.department, &s.semester, s.phone) != EOF) {
        printf("%-10d | %-20s | %-15s | %-8d | %-15s\n", 
               s.id, s.name, s.department, s.semester, s.phone);
        count++;
    }
    
    fclose(file);
    if (count == 0) {
        printf("No records in file.\n");
    }
}