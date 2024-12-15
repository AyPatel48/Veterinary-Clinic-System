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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

void sortAppointments(struct Appointment appointments[], int max) {

    int i = 0, j = 0;
    struct Appointment temp;

    //Calculating all the time and time values in minutes for comparison
    for (i = 0; i < max; i++) {

        appointments[i].time.min = (appointments[i].date.year * 12 * 30 * 24 * 60) +
            (appointments[i].date.month * 30 * 24 * 60) +
            (appointments[i].date.day * 24 * 60) +
            (appointments[i].time.hour * 60) +
            (appointments[i].time.min);
    
    }

    //This iteration compares the time of appointments in minutes and then sorts them up..
    for (i = max - 1; i > 0; i--) {

        for (j = 0; j < i; j++) {

            if (appointments[j].time.min > appointments[j + 1].time.min) {

                //Swapping the structs
                temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            
            }
        }
    }

    //Converting total minutes back to original minutes
    for (i = 0; i < max; i++) {

        appointments[i].time.min = appointments[i].time.min -
            (appointments[i].date.year * 12 * 30 * 24 * 60) -
            (appointments[i].date.month * 30 * 24 * 60) -
            (appointments[i].date.day * 24 * 60) -
            (appointments[i].time.hour * 60);

    }
    
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {

    //Declaration of variables and structs
    int i = 0, eligibility = 0;

    //If format is table, then only display the header
    if (fmt == FMT_TABLE) {
        //Display the patient table header
        displayPatientTableHeader();
    }

    //Iterate to display the data of all patients
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            eligibility = 1;
        }
    }

    //If no data was found..
    if (!eligibility) {

        //In case, no records are found
        printf("*** No records found ***\n\n");

    }

    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {

    //Declaration of variables and structs
    int selection;

    //Selection options for user
    do {
        //Display the search options
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");

        //Prompt the user for selection
        selection = inputIntRange(0, 2);
        printf("\n");

        if (selection == 1) {
            //If the user wants to search the patient by patient number
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2) {
            //If the user wants to search the patient by patient's phone number
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection != 0);

}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {

    //Declaration of variables and structs
    int i = 0,flag = 1, position = 0;

    //Iterate through the array to check if there is any empty slot
    //or if any patient was removed and it is in a safe empty state
    do {
        if (patient[i].patientNumber == 0) {
            position = i;
            flag = 0;
        }
        else {
            flag = 1;
        }
        i++;
    } while (flag);


    if (position < max)
    {
        //If eleigible, ask for the patient details and store it..
        patient[position].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[position]);
        //Patient added Confirmation Message
        printf("*** New patient record added ***\n\n");
    }
    else {
        //In case, patient listing is full
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {

    //Declaration of variables and structs
    int patientNum, index;

    //Ask the user for patient number
    printf("Enter the patient number: ");
    patientNum = inputInt();
    printf("\n");

    //Get the index from the patient number
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index != -1) {
        //If index is not equal to zero, display the edit patient menu
        menuPatientEdit(&patient[index]);
    }
    else {
        //In case, no records were found
        printf("*** No records found ***\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {

    //Declaration of variables and structs
    int patientNum = 0, index = 0;
    char selection;

    //Prompt the user for the patient number
    printf("Enter the patient number: ");
    patientNum = inputInt();
    printf("\n");

    //Get the index number of the patient
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index != -1) {
        //Display Patient data
        displayPatientData(&patient[index], FMT_FORM);

        printf("\n");

        //Ask if the user really want to remove the patient data from the system
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");

        if (selection == 'n') {
            //Abort the operation of removing the patient data
            printf("Operation aborted.\n\n");
        }
        else {
            //If selection == 'y' or selection == 'Y', remove the patient record
            //and assign it to a safe empty state, so that the other funtion 
            //can't access it
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
    }
    else {
        //If patient record is not found..
        printf("ERROR: Patient record not found!\n\n");
    }


}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) {

    //Declaration of variables
    int i, j;

    //Sorting the appointments in case some data is changed
    sortAppointments(data->appointments, data->maxAppointments);

    //Displaying Patient Data after sorting
        
        //Display the Schedule Table Header
        displayScheduleTableHeader(NULL, 1);

        //Display all patients data who have an appointment
        for (i = 0; i < data->maxAppointments; i++) {

            for (j = 0; j < data->maxPatient; j++) {

                if (data->appointments[i].patientNumber && data->patients[j].patientNumber) {

                    if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {

                        displayScheduleData(&data->patients[j], &data->appointments[i], 1);

                    }

                }

            }

        }
    
    //New Line
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {

    //Declaration of variables and structs
    int lastDay = 31;
    int i = 0, j = 0;
    struct Date date;

    //Taking the year as Input
    printf("Year        : ");
    date.year = inputIntPositive();

    //Taking the month as Input
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    //Taking the day as Input
    printf("Day (1-");

    if (date.month == 4 || date.month == 9 ||
        date.month == 6 || date.month == 11) {

        lastDay = 30;

    }
    else if (date.year % 4 != 0 && date.month == 2) {

        lastDay = 28;

    }
    else if (date.year % 4 == 0 && date.month == 2) {

        lastDay = 29;

    }
    printf("%d)  : ", lastDay);
    
    date.day = inputIntRange(1, lastDay);
    printf("\n");

    //Sort the appointments
    sortAppointments(data->appointments, data->maxAppointments);

    //Display Schedule Table Header
    displayScheduleTableHeader(&date, 0);

    //Iterate to display all the scheduled appointments
    for (i = 0; i < data->maxAppointments; i++) {

        for (j = 0; j < data->maxPatient; j++) {

            if (data->appointments[i].patientNumber && 
                data->patients[j].patientNumber) {

                if (data->appointments[i].patientNumber == 
                    data->patients[j].patientNumber) {

                    if (data->appointments[i].date.year == date.year && 
                        data->appointments[i].date.month == date.month && 
                        data->appointments[i].date.day == date.day) {

                        displayScheduleData(&data->patients[j], 
                            &data->appointments[i], 0);

                    }
                }
            }
        }
    }

    printf("\n");

}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointment, int maxAppointments,
    struct Patient* patient, int maxPatients) {

    //Declaration of variables and two temporary structs
    struct Date date;
    struct Time time;
    int lastDay = 31, patientNumber, index, slotNotAvailable = 1;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);

    if (index >= 0) {
        while (slotNotAvailable)
        {
            // Taking the year as input
            printf("Year        : ");
            date.year = inputIntPositive();

            // Taking the month as input
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            // Taking the day as input
            printf("Day (1-");
            if (date.month == 4 || date.month == 9 || date.month == 11) {
                lastDay = 30;
            }
            if (date.month == 2) {
                lastDay = 28;
            }
            if (date.year % 4 == 0 && date.month == 2) {
                lastDay = 29;
            }

            printf("%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);

            //Taking the hour as input
            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            //Taking the min as input
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Checking whether time slot is available
            if (timeSlotAvailability(date, time, appointment, maxAppointments)) {

                //Validation Message
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            
            }
            else {

                while ((time.hour < START_HOUR || time.hour > END_HOUR) || 
                    (time.hour == END_HOUR && time.min > 0) || 
                    (time.min % MIN_INTERVAL != 0)) {

                    //Validation Message
                    printf("ERROR: Time must be between %02d:00 and %02d:00 ", START_HOUR, END_HOUR);
                    printf("in %02d minute intervals.\n\n", MIN_INTERVAL);

                    //Prompt again for hour and min inputs
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);

                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                //In case the slot is not available..
                slotNotAvailable = 0;

            }
        }

        // Assigning the values to the next available slot
        index = nextEmptySlot(appointment, maxAppointments);
        appointment[index].date = date;
        appointment[index].time = time;
        appointment[index].patientNumber = patientNumber;

        //Appointment Schedule Confirmation Message
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else {
        //Validation Message
        printf("\nERROR: Patient record not found!\n\n");
    
    }
    return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointment, int maxAppointments,
    struct Patient* patient, int maxPatients) {

    //Declaration of variables and structs
    struct Date date;
    int ptindex, patientNumber, lastDay = 0, aptIndex;

    // Taking the patient number as input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    ptindex = findPatientIndexByPatientNum(patientNumber, patient, maxPatients);

    if (ptindex >= 0) {

        // Prompting for year
        printf("Year        : ");
        date.year = inputIntPositive();

        // Prompting for month
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        // Prompting for day
        printf("Day (1-");
        if (date.month == 4 || date.month == 9 || date.month == 11) {
            lastDay = 30;
        }
        if (date.month == 2) {
            lastDay = 28;
        }
        if (date.year % 4 == 0 && date.month == 2) {
            lastDay = 29;
        }
        printf("%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);

        //Get Appointment Index
        aptIndex = AppointmentValidity(patientNumber, date, appointment, maxAppointments);

        if (aptIndex >= 0) {
            printf("\n");

            //Display Patient Data and ask user to confirm the deletion of that appointment
            displayPatientData(&patient[ptindex], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') {
                appointment[aptIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }

            else {
                //If there are no appointments scheduled on that particular day
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else {
        //If patient data was not found..
        printf("ERROR: Patient record not found!\n\n");
    }

}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {

    //Declaration of variables and structs
    int patientNum = 0, index = 0;

    //Prompt the user for patient number
    printf("Search by patient number: ");
    patientNum = inputInt();
    printf("\n");

    //Get the index number...
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index != -1) {
        //Display the patient data if found..
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    }
    else {
        //If no records are found
        printf("*** No records found ***\n\n");
    }

}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {

    //Declaring the variables and structs
    int i = 0, match = 0;
    char phnNum[PHONE_LEN + 1];

    //Prompt the user for the patient number
    printf("Search by phone number: ");
    inputCString(phnNum, 0, PHONE_LEN + 1);
    printf("\n");

    //Display Patient Table Header
    displayPatientTableHeader();

    //Iterate through the array to find the matching phone number
    for (i = 0; i < max + 1; i++)
    {
        //If the phone number matches, call displayPatientData
        if (strcmp(patient[i].phone.number, phnNum) == 0)
        {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);

            match++;
        }
    }

    printf("\n");

    //In case, no records are found, display the error message
    if (match == 0)
    {
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {

    //Declaration of variables and structs
    int nextPtNum = 0, maxNum = patient[0].patientNumber, i = 0;

    //Iterate through the array to find the max patient number
    for (i = 0; i < max; i++) {

        //If the next patient number is greater than the maxNum, 
        //it is assigned to maxNum
        if (patient[i].patientNumber > maxNum)
        {
            maxNum = patient[i].patientNumber;
        }
    }

    //The next patient number is the maxNum + 1
    nextPtNum = maxNum + 1;

    //Return the next Patient number
    return nextPtNum;

}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) {

    //Declaration of variables and structs
    int i;

    //Iterate through the array to find the patient number
    for (i = 0; i < max; i++)
    {
        //If patient number is found, return the index
        if (patient[i].patientNumber == patientNumber) {
            return i;
        }
    }

    //If not found, -1 is returned
    return -1;
}

//Checks whether a time slot is available
int timeSlotAvailability(struct Date date, struct Time time,
    struct Appointment* appointment, int maxAppointments) {

    int i, IsslotAvailable = 0;

    for (i = 0; i < maxAppointments; i++) {

        // Checking if time slot is available
        if (date.year == appointment[i].date.year && 
            date.month == appointment[i].date.month && 
            date.day == appointment[i].date.day && 
            time.hour == appointment[i].time.hour && 
            time.min == appointment[i].time.min) {

            IsslotAvailable = 1;
        }
    }

    return IsslotAvailable;

}

//Gives the next empty time slot
int nextEmptySlot(struct Appointment* appointment, int maxAppointments) {

    //Declaration of variables and structs
    int i = 0, available = 0;

    //Iterate to find out if there is any empty slot in the record..
    while (available == 0 && i < maxAppointments) {

        if (appointment[i].patientNumber < 1) {

            available = 1;

        }
        i++;
    }

    //Return the position at which the slot is empty..
    return i;
}

//Checks the validity of the appointment
int AppointmentValidity(int patientNumber, struct Date date,
    struct Appointment* appointment, int maxAppointments) {

    //Declaration of variables and structs
    int i = 0, valid = 0;

    //Iterate to check if the appointment is valid or not..
    while (valid == 0 && i < maxAppointments)
    {
        if ((appointment[i].patientNumber == patientNumber) && 
            (appointment[i].date.day == date.day) && 
            (appointment[i].date.month == date.month) && 
            (appointment[i].date.year == date.year)) {

            valid = 1;

        }
        i++;
    }
    return i - 1;

}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {


    //Display Patient data input header
    printf("Patient Data Input\n");
    printf("------------------\n");

    //Prompt the user for patient name
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);

    printf("\n");

    //Get patient's phone number
    inputPhoneData(&patient->phone);

}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {

    //Declaration of variables and structs
    int selection = 0;

    //Display the phone information header
    printf("Phone Information\n");
    printf("-----------------\n");

    //Display the ways of contacting the patient menu
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");

    //Asking the user to select their next movement..
    printf("Selection: ");
    selection = inputIntRange(1, 4);

    printf("\n");

    if (selection == 1 || selection == 2 || selection == 3)
    {
        //If the user's phone number is a CELL phone number
        if (selection == 1) {
            //Storing the description 
            strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        }

        //If the user's phone number is a HOME phone number
        if (selection == 2) {
            //Storing the description 
            strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        }

        //If the user's phone number is a WORK phone number
        if (selection == 3) {
            //Storing the description 
            strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        }

        // Displaying description
        printf("Contact: %s\n", phone->description);


        // Asking the user for a number as input and storing it in struct
        printf("Number : ");
        inputCStringNumbers(phone->number, PHONE_LEN, PHONE_LEN);

        printf("\n");
    }
    //If the user's phone number is To Be Discussed...
    else if (selection == 4) {

        // Storing the description in the struct
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);

        *phone->number = 0;

    }
    //Else print the error message..
    else {
        printf("Error:\n");
    }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {

    //Declaration of variables
    int count = 0, flag = 1;

    // Opening the file
    FILE* fp;
    fp = fopen(datafile, "r");

    // If file is empty..
    if (fp != NULL) {
        count = 0;

        //Iterating until the EOF
        while (flag == 1 && (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[count].patientNumber,
            patients[count].name,
            patients[count].phone.description,
            patients[count].phone.number) != EOF))
        {
            count++;
            if (count >= max)
            {
                flag = 0;
            }
        }

        // Closing the file
        fclose(fp);
    }

    else {
        //Validation Message
        printf("ERROR: File could not be read\n");
    }

    // Return the number of records read
    return count;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {

    // Declaration of variables
    int i, count = 0;

    // Opening the file
    FILE* fp;
    fp = fopen(datafile, "r");

    // If file is empty..
    if (fp != NULL) 
    {

        // Reading and storing the file data into the appropriate places
        for (i = 0; i < max && !feof(fp); i++) {

            // Reading values from file and storing them
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, 
                &appoints[i].date.month, &appoints[i].date.day, 
                &appoints[i].time.hour, &appoints[i].time.min);

            // Checking for EOF..
            if (!feof(fp)) {

                //If EOF is not reached, increment the count by 1
                count++;

            }
        }

        // Closing the file
        fclose(fp);
    }
    else 
    {
        //In case the file has some errors..
        printf("ERROR: File could not be read\n");
    }

    // Return the number of records read
    return count;
}