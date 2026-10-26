#include <stdio.h>
#include "timetable.h"
#include "file_utils.h"

#define TIMETABLE_FILE "data/timetable.txt"

void timetable_menu() {
    int choice;
    do {
        printf("\n--- Timetable Management ---\n");
        printf("1. Add Class Schedule\n2. View All Classes\n3. Back\nChoice: ");
        choice = get_int();

        if (choice == 1) {
            char day[15], time[15], subject[30], room[10];
            printf("Day (e.g., Monday): "); get_string(day, sizeof(day));
            printf("Time (e.g., 10:00AM): "); get_string(time, sizeof(time));
            printf("Subject: "); get_string(subject, sizeof(subject));
            printf("Room Number: "); get_string(room, sizeof(room));

            FILE *f = fopen(TIMETABLE_FILE, "a");
            if (f) {
                fprintf(f, "%s|%s|%s|%s\n", day, time, subject, room);
                fclose(f);
                printf("Class added to timetable!\n");
            }
        } 
        else if (choice == 2) {
            char day[15], time[15], subject[30], room[10];
            FILE *f = fopen(TIMETABLE_FILE, "r");
            if (!f) { printf("No timetable found.\n"); continue; }
            
            printf("\n%-10s | %-10s | %-20s | %-10s\n", "Day", "Time", "Subject", "Room");
            printf("-----------------------------------------------------------\n");
            while (fscanf(f, "%14[^|]|%14[^|]|%29[^|]|%9[^\n]\n", day, time, subject, room) != EOF) {
                printf("%-10s | %-10s | %-20s | %-10s\n", day, time, subject, room);
            }
            fclose(f);
        }
    } while(choice != 3);
}