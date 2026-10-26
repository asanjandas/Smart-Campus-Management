#ifndef COMPLAINT_H
#define COMPLAINT_H

typedef struct {
    int id;
    int student_id;
    char category[30];
    char description[100];
    char status[20]; // Pending, In Progress, or Resolved
} Complaint;

void complaint_menu();
void log_complaint();
void view_complaints();
void update_complaint_status();

#endif