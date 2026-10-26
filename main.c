#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "student.h"
#include "complaint.h"
#include "notice.h"
#include "feedback.h"
#include "faculty.h"
#include "attendance.h"
#include "timetable.h"
#include "reports.h"

int main() {
    int choice;
    
    // Ensure the data directory exists silently
    system("mkdir data 2> nul"); 
    
    do {
        printf("\n==========================================\n");
        printf("   SMART CAMPUS MANAGEMENT SYSTEM (SCMS)  \n");
        printf("==========================================\n");
        printf("1. Student Information Management\n");
        printf("2. Faculty Directory\n");
        printf("3. Attendance Management\n");
        printf("4. Timetable Management\n");
        printf("5. Complaints Management\n");
        printf("6. Notice Board\n");
        printf("7. Feedback & Suggestions\n");
        printf("8. Campus Reports & Statistics\n");
        printf("9. Exit System\n");
        printf("Select a module (1-9): ");
        
        choice = get_int();

        switch(choice) {
            case 1: student_menu(); break;
            case 2: faculty_menu(); break;
            case 3: attendance_menu(); break;
            case 4: timetable_menu(); break;
            case 5: complaint_menu(); break;
            case 6: notice_menu(); break;
            case 7: feedback_menu(); break;
            case 8: reports_menu(); break;
            case 9: printf("\nExiting SCMS. Best of luck with your project!\n"); break;
            default: printf("\nInvalid selection. Please enter a valid number between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}