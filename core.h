/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : AYUSHKUMAR VIPULBHAI PATEL
Student ID#: 114473226
Email      : apatel574@myseneca.ca
Section    : G

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//1. inputInt Prototype
int inputInt(void);

//2. inputIntPositive Prototype
int inputIntPositive(void);

//3. inputIntRange Prototype
int inputIntRange(int upper_bound, int lower_bound);

//4. inputCharOption Prototype
char inputCharOption(char valid_chars[]);

//5. inputCString Prototype
void inputCString(char* C_String, int lower_bound, int upper_bound);

//6. inputCStringNumbers Prototype
void inputCStringNumbers(char* C_String, int lower_bound, int upper_bound);

//7. displayFormattedPhone Prototype
void displayFormattedPhone(const char* phn_no);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
