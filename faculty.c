#include <stdio.h>
#include "faculty.h"
#include "file_utils.h"

#define FACULTY_FILE "data/faculty.txt"

void faculty_menu() {
    int choice;
    do {
        printf("\n--- Faculty Directory ---\n");
        printf("1. Add Faculty Member\n2. View All Faculty\n3. Back to Main Menu\nChoice: ");
        choice = get_int();

        if (choice == 1) {
            char id[10], name[50], dept[30], subject[30];
            printf("Enter Faculty ID: "); get_string(id, sizeof(id));
            printf("Enter Name: "); get_string(name, sizeof(name));
            printf("Enter Department: "); get_string(dept, sizeof(dept));
            printf("Enter Subject: "); get_string(subject, sizeof(subject));

            FILE *f = fopen(FACULTY_FILE, "a");
            if (f) {
                fprintf(f, "%s|%s|%s|%s\n", id, name, dept, subject);
                fclose(f);
                printf("Faculty added successfully!\n");
            }
        } 
        else if (choice == 2) {
            char id[10], name[50], dept[30], sub[30];
            FILE *f = fopen(FACULTY_FILE, "r");
            if (!f) { printf("No records found.\n"); continue; }
            
            printf("\n%-10s | %-20s | %-15s | %-15s\n", "ID", "Name", "Department", "Subject");
            printf("----------------------------------------------------------------------\n");
            while (fscanf(f, "%9[^|]|%49[^|]|%29[^|]|%29[^\n]\n", id, name, dept, sub) != EOF) {
                printf("%-10s | %-20s | %-15s | %-15s\n", id, name, dept, sub);
            }
            fclose(f);
        }
    } while(choice != 3);
}