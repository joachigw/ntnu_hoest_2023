#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * Stack struct that is used to store opening brackets.
 */
typedef struct {
    int* table;
    int count, max;
} Stack;

/**
 * Creates a new stack.
 * @param initial_capacity initial maximum capacity of opening brackets.
 * @return the new Stack structure.
 */
Stack* newStack(int initial_capacity) {
    Stack* s = (Stack *)(malloc(sizeof(Stack)));
    s->table = (malloc(sizeof(int) * initial_capacity));
    s->count = 0;
    s->max = initial_capacity;
    return s;
}

/**
 * Checks whether the stack is empty or not.
 * @param s the stack to check the size of.
 * @return true if the stack is empty, false if not.
 */
bool emptyStack(Stack* s) {
    return s->count == 0;
}

/**
 * Checks if the stack has reached its size limit.
 * @param s the stack to check the size of.
 * @return true if the stack is full, false if not.
 */
bool fullStack(Stack* s) {
    return s->count == s->max;
}

/**
 * Resize the stack when it becomes full.
 * @param s the stack to be resized.
 */
void resizeStack(Stack* s) {
    // Double the max size value of the stack
    s->max *= 2;
    // Attempt to increase the size of the allocated memory for the stack
    int* temp = (int*)(realloc(s->table, sizeof(char) * s->max));
    if (temp == NULL) {
        printf("\n### Failed to resize the stack! ###\n");
        exit(1);
    }
    s->table = temp;
}

/**
 * Stores a char (as an int due to fgetc()) (opening bracket) inside the stack.
 * @param s the stack to store the character in.
 * @param c the character to store.
 */
void push(Stack* s, int c) {
    if (!fullStack(s)) {
        s->table[s->count++] = c;
    } else resizeStack(s);
}

/**
 * Removes the topmost opening bracket (the one pushed in last).
 * @param s the stack to remove the topmost opening bracket from.
 */
void pop(Stack* s) {
    if (!emptyStack(s)) {
        --s->count;
    }
}

/**
 * Reads the topmost opening bracket in the stack.
 * @param s the stack to read from.
 * @return the topmost opening bracket,
 */
int checkStack(Stack* s) {
    if (emptyStack(s)) return '\0';
    return s->table[s->count - 1];
}

int main() {
    FILE* fptr;
    int c;
    int line_number = 1;
    int char_position = 0;

    // Boolean states used to determine whether the read characters belong to a string or not
    bool inString = false;
    bool inBlockComment = false;
    bool inLineComment = false;

    // Open file read stream
    char fileName[] = "fileHandling.java";
    fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        printf("Unable to locate or read the file '%s'!\n", fileName);
        return 1;
    } else printf("File opened successfully!\nReading the file '%s' character by character...\n\n", fileName);

    // Initialize the stack with an initial capacity
    Stack* stack = newStack(20);

    // Read the opened file character by character, and store encountered opening brackets in the Stack struct
    while ((c = fgetc(fptr)) != EOF) {

        // Update the position of the character being read
        char_position++;
        if (c == '\n') {
            line_number++;
            char_position = 0;
        }

        // Keeps track of whether the characters are inside a string or not
        if ((c == '"' || c == '\'') && !inBlockComment && !inLineComment) {
            inString = !inString;
        }

        // Handles characters that are not part of any type of comment or string
        if (!inString && !inBlockComment && !inLineComment) {

            // Stores the opening brackets if encountered
            if (c == '(' || c == '[' || c == '{') {
                push(stack, c);
            }

            // Check whether the closing bracket matches the one at the top of the stack
            else if (c == ')' || c == ']' || c == '}') {
                int top = checkStack(stack);
                if (top == '\0') {
                    printf("ERROR: Extra closing bracket '%c' at line %d, position %d!\n",
                           c, line_number, char_position);
                    return 1;
                }
                if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{')) {
                    pop(stack);
                } else {
                    printf("ERROR: Mismatched brackets '%c' and '%c' at line %d, position %d!\n",
                           top, c, line_number, char_position);
                    return 1;
                }
            }
        }

        // Checks for the start of a single or multi-line comment
        if (c == '/' && !inString && !inBlockComment && !inLineComment) {
            char nextChar = fgetc(fptr);
            if (nextChar == '*') inBlockComment = true;
            else if (nextChar == '/') inLineComment = true;
            else ungetc(nextChar, fptr);
        }

        // Checks for the end of a multi-line comment
        if (c == '*' && inBlockComment) {
            char nextChar = fgetc(fptr);
            if (nextChar == '/') inBlockComment = false;
        }

        // Checks for the end of a single line comment
        if (c == '\n' && inLineComment) {
            inLineComment = false;
        }
    }

    // Check if the stack is empty
    if (!emptyStack(stack)) {
        int top = checkStack(stack);
        printf("Unbalanced: Unmatched opening bracket '%c' at line %d, position %d!\n",
               top, line_number, char_position);
        return 1;
    }

    // Close file
    fclose(fptr);
    printf("SUCCESS: All brackets are properly nested!");
    return 0;
}