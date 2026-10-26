#include <stdio.h>
#include <string.h>
#include "attendance.h"
#include "file_utils.h"

#define ATTENDANCE_FILE "data/attendance.txt"

void attendance_menu() {
    int choice;
    do {
        printf("\n--- Attendance Management ---\n");
        printf("1. Mark Daily Attendance\n2. Check Student Percentage\n3. Back\nChoice: ");
        choice = get_int();

        if (choice == 1) {
            char date[15], status[5];
            int student_id;
            printf("Enter Date (DD-MM-YYYY): "); get_string(date, sizeof(date));
            printf("Enter Student ID: "); student_id = get_int();
            printf("Status (P for Present, A for Absent): "); get_string(status, sizeof(status));

            FILE *f = fopen(ATTENDANCE_FILE, "a");
            if (f) {
                fprintf(f, "%s|%d|%s\n", date, student_id, status);
                fclose(f);
                printf("Attendance logged!\n");
            }
        } 
        else if (choice == 2) {
            int target_id, file_id, total = 0, present = 0;
            char date[15], status[5];
            
            printf("Enter Student ID to check: ");
            target_id = get_int();

            FILE *f = fopen(ATTENDANCE_FILE, "r");
            if (!f) { printf("No attendance data found.\n"); continue; }

            while (fscanf(f, "%14[^|]|%d|%4[^\n]\n", date, &file_id, status) != EOF) {
                if (file_id == target_id) {
                    total++;
                    if (strcmp(status, "P") == 0 || strcmp(status, "p") == 0) {
                        present++;
                    }
                }
            }
            fclose(f);

            if (total == 0) {
                printf("No attendance records for Student ID %d.\n", target_id);
            } else {
                float percentage = ((float)present / total) * 100.0;
                printf("\nStudent %d Attendance: %.2f%% (%d/%d classes)\n", target_id, percentage, present, total);
            }
        }
    } while(choice != 3);
}