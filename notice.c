#include <stdio.h>
#include "notice.h"
#include "file_utils.h"

#define NOTICE_FILE "data/notices.txt"

void notice_menu() {
    int choice;
    do {
        printf("\n--- Digital Notice Board ---\n");
        printf("1. Post a New Notice (Admin)\n");
        printf("2. View All Notices\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        choice = get_int();

        switch(choice) {
            case 1: add_notice(); break;
            case 2: view_notices(); break;
            case 3: printf("Returning...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 3);
}

void add_notice() {
    char date[15], title[50], content[150];
    
    printf("\nEnter Date (DD-MM-YYYY): ");
    get_string(date, sizeof(date));
    
    printf("Enter Notice Title: ");
    get_string(title, sizeof(title));
    
    printf("Enter Notice Content: ");
    get_string(content, sizeof(content));

    FILE *file = fopen(NOTICE_FILE, "a");
    if (file == NULL) {
        printf("Error saving notice.\n");
        return;
    }

    fprintf(file, "%s|%s|%s\n", date, title, content);
    fclose(file);
    printf("Notice posted successfully!\n");
}

void view_notices() {
    FILE *file = fopen(NOTICE_FILE, "r");
    if (file == NULL) {
        printf("\nNo notices on the board.\n");
        return;
    }

    char date[15], title[50], content[150];
    printf("\n================= CAMPUS NOTICES =================\n");
    
    while (fscanf(file, "%14[^|]|%49[^|]|%149[^\n]\n", date, title, content) != EOF) {
        printf("\nDate: %s\n", date);
        printf("Subject: %s\n", title);
        printf("Details: %s\n", content);
        printf("--------------------------------------------------\n");
    }
    fclose(file);
}