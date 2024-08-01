#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h> // Include header file for getch function on Windows

#define MAX_PATIENTS 100
#define TABLE_SIZE 10

// Function prototype for readPassword
void readPassword(char *password);

// Structure to represent a patient
typedef struct
{
    char name[50];
    int age;
    char address[100];
    char disease[100];
    char lastAppointment[100];
    char drugsPrescribed[100];
    char doctorAlloted[50];
    float bloodPressure;
    float sugarLevel;
} Patient;

// Define a structure for a node in the linked list
typedef struct ListNode
{
    Patient *patient;      // Pointer to a patient
    struct ListNode *next; // Pointer to the next node in the linked list
} ListNode;

// Global hash table to store linked lists of patients
ListNode *hashTable[TABLE_SIZE] = {NULL};

// Global variable to track the number of patients
int patientCount = 0;
int totalDoctors = 0;
int lastAllottedDoctorIndex = -1;
char doctors[MAX_PATIENTS][100];

// Function to compute the hash value for a given age
int hashFunction(int age)
{
    return age % TABLE_SIZE;
}

int isValidDate(const char *date)
{
    if (strlen(date) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return 0;
        }
        else
        {
            if (!isdigit(date[i]))
                return 0;
        }
    }
    return 1;
}

void addPatient()
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("Maximum number of patients reached.\n");
        return;
    }

    Patient *newPatient = (Patient *)malloc(sizeof(Patient)); // Allocate memory for a new patient

    // Read patient details from the user
    printf("Enter patient name: ");
    while ((getchar()) != '\n')
        ;

    int validName = 0;

    do
    {
        scanf(" %[^\n]s", newPatient->name);

        int i = 0;
        // Validate name - should only contain alphabets and spaces
        for (i = 0; newPatient->name[i] != '\0'; ++i)
        {
            if (!(isalpha(newPatient->name[i]) || newPatient->name[i] == ' '))
            {
                printf("Invalid name. Please enter a valid name.\n");
                break;
            }
            i++;
        }
        if (!newPatient->name[i])
            validName = 1;
    } while (!validName && strlen(newPatient->name) > 0);

    // Read patient age from the user
    int ageInput;
    printf("Enter patient age: ");
    while (scanf("%d", &ageInput) != 1 || ageInput <= 0 || ageInput > 150)
    {
        printf("Invalid age. Please enter a valid age (1-150).\n");
        while ((getchar()) != '\n')
            ; // Clear input buffer
        printf("Enter patient age: ");
    }
    newPatient->age = ageInput;

    printf("Enter patient address: ");
    scanf(" %[^\n]s", newPatient->address);

    printf("Disease(s) Diagnosed in Past: ");
    scanf(" %[^\n]s", newPatient->disease);

    do
    {
        printf("Enter last appointment date(YYYY-MM-DD): ");
        scanf(" %s", newPatient->lastAppointment);
        if (!isValidDate(newPatient->lastAppointment))
            printf("Invalid Date Format. Please enter a valid date in the format YYYY-MM-DD.\n");
    } while (!isValidDate(newPatient->lastAppointment));

    printf("Enter drugs prescribed last time: ");
    scanf(" %[^\n]s", newPatient->drugsPrescribed);

    printf("Enter the level of Blood Pressure: ");
    scanf("%f", &newPatient->bloodPressure);

    printf("Enter the Sugar level: ");
    scanf("%f", &newPatient->sugarLevel);

    // Allot the next available doctor
    if (totalDoctors == 0)
    {
        printf("No doctors available.\n");
        return;
    }

    lastAllottedDoctorIndex = (lastAllottedDoctorIndex + 1) % totalDoctors;
    strcpy(newPatient->doctorAlloted, doctors[lastAllottedDoctorIndex]);
    printf("Doctor Assigned: %s\n", newPatient->doctorAlloted);

    // Compute the hash index for the patient's age
    int index = hashFunction(newPatient->age);

    // Create a new node for the patient
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->patient = newPatient;
    newNode->next = NULL;

    // Handle collisions by adding the new node to the linked list at the hash table index
    if (hashTable[index] == NULL)
    {
        hashTable[index] = newNode;
    }
    else
    {
        ListNode *current = hashTable[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Patient added successfully.\n");
    patientCount++;
}

// Function to update an existing patient record
void updatePatient()
{
    char updateName[50];
    printf("Enter patient name to update: ");
    scanf(" %[^\n]s", updateName);

    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at the current hash table index
        ListNode *current = hashTable[i];
        while (current != NULL)
        {
            if (strcmp(current->patient->name, updateName) == 0)
            {
                // Update patient details
                printf("Enter new patient name: ");
                scanf(" %[^\n]s", current->patient->name);

                printf("Enter new patient age: ");
                scanf("%d", &current->patient->age);

                printf("Enter new patient address: ");
                scanf(" %[^\n]s", current->patient->address);

                printf("Enter the name of Disease Diagnosed in Past: ");
                scanf(" %[^\n]s", current->patient->disease);

                printf("Enter the level of Blood Pressure: ");
                scanf("%f", &current->patient->bloodPressure);

                printf("Enter the Sugar level: ");
                scanf("%f", &current->patient->sugarLevel);

                printf("Patient record updated successfully.\n");
                found = 1;
                break; // Exit the loop once patient is found and updated
            }
            current = current->next;
        }
        if (found)
        {
            break; // Exit the outer loop once patient is found and updated
        }
    }

    if (!found)
    {
        printf("Patient not found.\n");
    }
}

// Function to delete an existing patient record
void deletePatient()
{
    char deleteName[50];
    printf("Enter patient name to delete: ");
    scanf(" %[^\n]s", deleteName);

    int hashIndex = hashFunction(0); // Default hash index to start traversal
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at the current hash table index
        ListNode *current = hashTable[hashIndex];
        ListNode *prev = NULL;
        while (current != NULL)
        {
            if (strcmp(current->patient->name, deleteName) == 0)
            {
                // Remove the patient record from the linked list
                if (prev != NULL)
                {
                    prev->next = current->next;
                }
                else
                {
                    hashTable[hashIndex] = current->next;
                }
                free(current->patient); // Free the memory allocated for the patient
                free(current);          // Free the memory allocated for the node
                printf("Patient record deleted successfully.\n");
                patientCount--;
                found = 1;
                break; // Exit the loop once patient is found and deleted
            }
            prev = current;
            current = current->next;
        }
        if (found)
        {
            break; // Exit the outer loop once patient is found and deleted
        }
        hashIndex = (hashIndex + 1) % TABLE_SIZE; // Move to the next hash table index
    }

    if (!found)
    {
        printf("Patient not found.\n");
    }
}

// Function to search for patients within a specified age range
void searchByAgeRange()
{
    int minAge, maxAge;
    printf("Enter minimum age: ");
    scanf("%d", &minAge);
    printf("Enter maximum age: ");
    scanf("%d", &maxAge);

    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at the current hash table index
        ListNode *current = hashTable[i];
        while (current != NULL)
        {
            if (current->patient->age >= minAge && current->patient->age <= maxAge)
            {
                printf("Name: %s\n Age: %d\n Address: %s\n Disease: %s\n Blood Pressure: %f\n Sugar Level: %f\n Doctor Assigned: %s\n",
                       current->patient->name, current->patient->age, current->patient->address, current->patient->disease,
                       current->patient->bloodPressure, current->patient->sugarLevel, current->patient->doctorAlloted);
                found = 1;
            }
            current = current->next;
        }
    }

    if (!found)
    {
        printf("No patients found in the given age range.\n");
    }
}

// Function to search for patients by age
void searchPatient()
{
    int searchAge;
    printf("Enter patient age to search: ");
    scanf("%d", &searchAge);

    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at the current hash table index
        ListNode *current = hashTable[i];
        while (current != NULL)
        {
            if (current->patient->age == searchAge)
            {
                // Print the details of the found patient
                printf("-----------------------------\n");
                printf("Name: %s\n", current->patient->name);
                printf("Age: %d\n", current->patient->age);
                printf("Address: %s\n", current->patient->address);
                printf("Disease Diagnosed in Past: %s\n", current->patient->disease);
                printf("Date of Last Appointment: %s\n", current->patient->lastAppointment);
                printf("Drugs Prescribed in Previous Appointment: %s\n", current->patient->drugsPrescribed);
                printf("Blood Pressure: %f\n", current->patient->bloodPressure);
                printf("Sugar Level: %f\n", current->patient->sugarLevel);
                printf("Doctor Assigned: %s\n", current->patient->doctorAlloted);
                printf("-----------------------------\n");
                found = 1;
            }
            current = current->next;
        }
    }

    if (!found)
    {
        printf("No patients found with the specified age.\n");
    }
}

bool authenticateUser()
{
    char username[50];
    char password[50];

    // Hardcoded username and password for demonstration purposes
    char correctUsername[] = "admin";
    char correctPassword[] = "staff";

    // Prompt the user for username and password
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    readPassword(password);
    printf("\n");

    // Check if the entered username and password match the correct ones
    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
    {
        return true; // Authentication successful
    }
    else
    {
        printf("Invalid username or password. Please try again.\n");
        return false; // Authentication failed
    }
}

void readPassword(char *password)
{
    int i = 0;
    while (1)
    {
        char ch = getch();
        if (ch == '\r')
        {
            password[i] = '\0';
            break;
        }
        else if (ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
}

// Function to display all patient records
void displayAllRecords()
{
    int found = 0; // Flag to indicate if any patients were found

    printf("All Patient Records:\n");

    // Iterate over each index in the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Check if the linked list at the current index is not empty
        if (hashTable[i] != NULL)
        {
            // Traverse the linked list and print each patient record
            ListNode *current = hashTable[i];
            while (current != NULL)
            {
                found = 1; // Set found flag
                printf("-----------------------------\n");
                printf("Name: %s\n", current->patient->name);
                printf("Age: %d\n", current->patient->age);
                printf("Address: %s\n", current->patient->address);
                printf("Disease Diagnosed in Past: %s\n", current->patient->disease);
                printf("Date of Last Appointment: %s\n", current->patient->lastAppointment);
                printf("Drugs Prescribed in Previous Appointment: %s\n", current->patient->drugsPrescribed);
                printf("Blood Pressure: %f\n", current->patient->bloodPressure);
                printf("Sugar Level: %f\n", current->patient->sugarLevel);
                printf("Doctor Assigned: %s\n", current->patient->doctorAlloted);
                printf("-----------------------------\n");

                // Move to the next node in the linked list
                current = current->next;
            }
        }
    }

    // If no records were found, display appropriate message
    if (!found)
    {
        printf("No patients found.\n");
    }
}

// Function to save patient records to a CSV file
void saveToFile()
{
    FILE *file = fopen("patients.csv", "w");
    // if (file == NULL)
    // {
    //     printf("Error opening file.\n");
    //     return;
    // }

    // Write header row
    fprintf(file, "Name,Age,Address,Disease,Last Appointment,Drugs Prescribed,Blood Pressure,Sugar Level,Doctor Alloted\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Traverse the linked list at the current hash table index
        ListNode *current = hashTable[i];
        while (current != NULL)
        {
            // Write each patient record in CSV format
            fprintf(file, "%s,%d,%s,%s,%s,%s,%.2f,%.2f,%s\n", current->patient->name, current->patient->age, current->patient->address,
                    current->patient->disease, current->patient->lastAppointment, current->patient->drugsPrescribed, current->patient->bloodPressure,
                    current->patient->sugarLevel, current->patient->doctorAlloted);
            current = current->next;
        }
    }

    fclose(file);
    printf("Records saved to CSV file successfully.\n");
}

int main()
{
    // Read doctors from file
    FILE *doctorFile = fopen("doctors.txt", "r");
    // if (doctorFile == NULL)
    // {
    //     printf("Error opening the file.\n");
    //     return 1;
    // }

    while (fgets(doctors[totalDoctors], sizeof(doctors[totalDoctors]), doctorFile) != NULL && totalDoctors < MAX_PATIENTS)
    {
        totalDoctors++;
    }

    fclose(doctorFile);

    if (!authenticateUser())
    {
        return 0; // Exit the program if authentication fails
    }

    int choice;

    // Once authenticated, display the menu options
    printf("*************Welcome to Medical Record Management system**************\n");
    do
    {
        printf("\n1. Add Patient\n");
        printf("2. Search Patient\n");
        printf("3. Update Patient Record\n");
        printf("4. Delete Patient Record\n");
        printf("5. Display All Records\n");
        printf("6. Search by Age Range\n");
        printf("7. Save Records to File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            searchPatient();
            break;
        case 3:
            updatePatient();
            break;
        case 4:
            deletePatient();
            break;
        case 5:
            displayAllRecords();
            break;
        case 6:
            searchByAgeRange();
            break;
        case 7:
            saveToFile();
            break;
        case 8:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}
