#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int id;
    char name[50];
    char department[30];
    int semester;
    char phone[15];
} Student;

void student_menu();
void add_student();
void display_students();
int check_duplicate_id(int id);

#endif