#include "file_utils.h"

void get_string(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        // Remove trailing newline AND carriage return (Crucial for Windows)
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
    }
}

int get_int() {
    char buffer[50];
    while (1) {
        get_string(buffer, sizeof(buffer));
        
        // If the user actually typed something, convert and return it
        if (strlen(buffer) > 0) {
            return atoi(buffer);
        }
        // If the input was empty (like a stray Enter key), the loop repeats 
        // and silently waits for real input without crashing the menu.
    }
}