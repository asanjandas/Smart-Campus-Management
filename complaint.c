#include <stdio.h>
#include <string.h>
#include "complaint.h"
#include "file_utils.h"

#define COMPLAINT_FILE "data/complaints.txt"
#define TEMP_FILE "data/temp.txt"

void complaint_menu() {
    int choice;
    do {
        printf("\n--- Campus Complaint Management ---\n");
        printf("1. Log a New Complaint\n");
        printf("2. View All Complaints\n");
        printf("3. Update Complaint Status (Admin)\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        choice = get_int();

        switch(choice) {
            case 1: log_complaint(); break;
            case 2: view_complaints(); break;
            case 3: update_complaint_status(); break;
            case 4: printf("Returning...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 4);
}

void log_complaint() {
    Complaint c;
    printf("\nEnter a new Complaint ID (e.g., 101): ");
    c.id = get_int();
    
    printf("Enter your Student ID: ");
    c.student_id = get_int();
    
    printf("Category (e.g., Cleaning, WiFi, Water): ");
    get_string(c.category, sizeof(c.category));
    
    printf("Brief Description: ");
    get_string(c.description, sizeof(c.description));
    
    strcpy(c.status, "Pending"); // Default status

    FILE *file = fopen(COMPLAINT_FILE, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d|%d|%s|%s|%s\n", c.id, c.student_id, c.category, c.description, c.status);
    fclose(file);
    printf("Complaint logged successfully! Status is 'Pending'.\n");
}

void view_complaints() {
    FILE *file = fopen(COMPLAINT_FILE, "r");
    if (file == NULL) {
        printf("\nNo complaints found.\n");
        return;
    }

    Complaint c;
    printf("\n%-5s | %-10s | %-15s | %-12s | %-30s\n", "ID", "Student ID", "Category", "Status", "Description");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fscanf(file, "%d|%d|%29[^|]|%99[^|]|%19[^\n]\n", 
           &c.id, &c.student_id, c.category, c.description, c.status) != EOF) {
        printf("%-5d | %-10d | %-15s | %-12s | %-30s\n", 
               c.id, c.student_id, c.category, c.status, c.description);
    }
    fclose(file);
}

void update_complaint_status() {
    int target_id, found = 0;
    printf("\nEnter the Complaint ID to update: ");
    target_id = get_int();

    FILE *file = fopen(COMPLAINT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w"); // Open a temporary file for writing

    if (file == NULL || temp == NULL) {
        printf("Error accessing files.\n");
        if(file) fclose(file);
        if(temp) fclose(temp);
        return;
    }

    Complaint c;
    while (fscanf(file, "%d|%d|%29[^|]|%99[^|]|%19[^\n]\n", 
           &c.id, &c.student_id, c.category, c.description, c.status) != EOF) {
        
        if (c.id == target_id) {
            found = 1;
            printf("Current Status: %s\n", c.status);
            printf("Enter New Status (e.g., Resolved, In Progress): ");
            get_string(c.status, sizeof(c.status));
        }
        // Write data (either updated or unchanged) to the temp file
        fprintf(temp, "%d|%d|%s|%s|%s\n", c.id, c.student_id, c.category, c.description, c.status);
    }

    fclose(file);
    fclose(temp);

    // Replace the old file with the new temp file
    remove(COMPLAINT_FILE);
    rename(TEMP_FILE, COMPLAINT_FILE);

    if (found) {
        printf("Complaint updated successfully.\n");
    } else {
        printf("Complaint ID not found.\n");
    }
}