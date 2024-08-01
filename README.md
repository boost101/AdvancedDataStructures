Medical Record Management System
This project is a Medical Record Management System written in C. It allows for managing patient records, including adding, searching, updating, deleting, displaying, and saving records to a CSV file. The system also includes authentication for secure access.

Table of Contents
Function Descriptions
hashFunction
isValidDate
addPatient
updatePatient
deletePatient
searchByAgeRange
searchPatient
authenticateUser
readPassword
displayAllRecords
saveToFile
Main Function
File Format
Function Descriptions
hashFunction

int hashFunction(int age);
Computes the hash value for a given age. The hash value is used to determine the index in the hash table where the patient record will be stored.

isValidDate
int isValidDate(const char *date);
Checks if a given date string is in the valid format YYYY-MM-DD.

addPatient
void addPatient();
Prompts the user to enter the details of a new patient, assigns a doctor, and stores the patient record in the hash table. Ensures validation of patient details before adding them to the system.

updatePatient
void updatePatient();
Prompts the user to enter the name of the patient whose record needs to be updated. If found, it allows the user to update the patient's details.

deletePatient
void deletePatient();
Prompts the user to enter the name of the patient whose record needs to be deleted. If found, it deletes the patient's record from the system.

searchByAgeRange
void searchByAgeRange();
Prompts the user to enter a minimum and maximum age. Searches and displays all patient records within the specified age range.

searchPatient
void searchPatient();
Prompts the user to enter the age of the patient they are searching for. Displays all patients matching the specified age.

authenticateUser
bool authenticateUser();
Prompts the user to enter a username and password for authentication. If the credentials match the hardcoded values, it returns true; otherwise, it returns false.

readPassword
void readPassword(char *password);
Reads the password from the user without displaying it on the screen. Used for secure password input.

displayAllRecords
void displayAllRecords();
Displays all patient records stored in the hash table.

saveToFile
void saveToFile();
Saves all patient records to a CSV file named patients.csv.

Main Function
int main();
The entry point of the program. Authenticates the user and displays a menu for various operations such as adding, searching, updating, deleting, displaying, and saving patient records.

File Format
doctors.txt
Contains a list of doctors. Each line represents a doctor's name.

patients.csv
Contains the patient records saved in CSV format. The columns include Name, Age, Address, Disease, Last Appointment, Drugs Prescribed, Blood Pressure, Sugar Level, and Doctor Alloted.

This README file provides a comprehensive overview of the functions and their purpose in the Medical Record Management System. Adjust any details according to your specific implementation and requirements.
