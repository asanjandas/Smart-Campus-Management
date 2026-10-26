#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to safely get string input without buffer overflow
void get_string(char *buffer, int size);

// Function to safely get integer input
int get_int();

#endif