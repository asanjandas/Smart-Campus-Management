#include <stdio.h>
#include "feedback.h"
#include "file_utils.h"

#define FEEDBACK_FILE "data/feedback.txt"

void feedback_menu() {
    int choice;
    do {
        printf("\n--- Feedback & Suggestions ---\n");
        printf("1. Submit Feedback\n");
        printf("2. View All Feedback\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        choice = get_int();

        switch(choice) {
            case 1: submit_feedback(); break;
            case 2: view_feedback(); break;
            case 3: printf("Returning...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 3);
}

void submit_feedback() {
    int student_id, rating;
    char comments[100];

    printf("\nEnter your Student ID: ");
    student_id = get_int();

    // Input validation loop
    do {
        printf("Rate campus facilities (1-5): ");
        rating = get_int();
        if(rating < 1 || rating > 5) {
            printf("Please enter a valid rating between 1 and 5.\n");
        }
    } while(rating < 1 || rating > 5);

    printf("Any suggestions? ");
    get_string(comments, sizeof(comments));

    FILE *file = fopen(FEEDBACK_FILE, "a");
    if (file == NULL) {
        printf("Error saving feedback.\n");
        return;
    }

    fprintf(file, "%d|%d|%s\n", student_id, rating, comments);
    fclose(file);
    printf("Thank you for your feedback!\n");
}

void view_feedback() {
    FILE *file = fopen(FEEDBACK_FILE, "r");
    if (file == NULL) {
        printf("\nNo feedback submitted yet.\n");
        return;
    }

    int id, rating;
    char comments[100];
    
    printf("\n%-10s | %-6s | %-40s\n", "Student ID", "Rating", "Comments");
    printf("--------------------------------------------------------------\n");
    
    while (fscanf(file, "%d|%d|%99[^\n]\n", &id, &rating, comments) != EOF) {
        printf("%-10d | %-6d | %-40s\n", id, rating, comments);
    }
    fclose(file);
}