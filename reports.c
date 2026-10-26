#include <stdio.h>
#include "reports.h"

// Helper function to count lines in a text file
int count_records(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    int count = 0;
    char ch;
    while (!feof(f)) {
        ch = fgetc(f);
        if (ch == '\n') count++;
    }
    fclose(f);
    return count;
}

void reports_menu() {
    printf("\n==========================================\n");
    printf("        CAMPUS STATISTICS REPORT          \n");
    printf("==========================================\n");
    
    printf("Total Registered Students : %d\n", count_records("data/students.txt"));
    printf("Total Faculty Members     : %d\n", count_records("data/faculty.txt"));
    printf("Total Complaints Logged   : %d\n", count_records("data/complaints.txt"));
    printf("Total Notices Posted      : %d\n", count_records("data/notices.txt"));
    printf("Total Feedback Entries    : %d\n", count_records("data/feedback.txt"));
    
    printf("\nPress Enter to return to Main Menu...");
    getchar(); // Waits for user to press enter
}