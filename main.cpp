#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // For nice formatting

using namespace std;

const string FILENAME = "student_data.txt";

struct Student {
    int rollNumber;
    string name;
    string grade;
    float marks;
};

// --- Function Prototypes ---
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void printHeader();

int main() {
    int choice;

    while (true) {
        // Simple menu UI
        cout << "\n==========================================" << endl;
        cout << "      STUDENT MANAGEMENT SYSTEM" << endl;
        cout << "==========================================" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: 
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}

// 1. ADD STUDENT
void addStudent() {
    Student s;
    ofstream outFile;
    
    // Open file in Append mode (ios::app)
    outFile.open(FILENAME, ios::app); 

    if (!outFile) {
        cout << "Error: File could not be opened!" << endl;
        return;
    }

    cout << "\n--- Add New Student ---" << endl;
    cout << "Enter Roll Number: ";
    cin >> s.rollNumber;
    cin.ignore(); // Clear the input buffer before taking string input
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Class/Grade: ";
    getline(cin, s.grade);
    cout << "Enter Marks: ";
    cin >> s.marks;

    // Writing to file. format: Roll | Name | Grade | Marks
    // We put newlines to make reading back easier
    outFile << s.rollNumber << endl;
    outFile << s.name << endl;
    outFile << s.grade << endl;
    outFile << s.marks << endl;

    outFile.close();
    cout << "Student record added successfully!" << endl;
}

// 2. DISPLAY ALL STUDENTS
void displayAllStudents() {
    Student s;
    ifstream inFile;
    inFile.open(FILENAME);

    if (!inFile) {
        cout << "Error: No data found. Try adding a student first." << endl;
        return;
    }

    printHeader();
    
    // Read the file until the end
    // Note: We read in the exact order we wrote (Roll -> Name -> Grade -> Marks)
    while (inFile >> s.rollNumber) {
        inFile.ignore(); 
        getline(inFile, s.name);
        getline(inFile, s.grade);
        inFile >> s.marks;
        inFile.ignore(); // Ignore newline after marks for next iteration

        cout << left << setw(10) << s.rollNumber 
             << setw(20) << s.name 
             << setw(10) << s.grade 
             << setw(10) << s.marks << endl;
    }
    
    inFile.close();
}

// 3. SEARCH STUDENT
void searchStudent() {
    int targetRoll;
    bool found = false;
    Student s;
    ifstream inFile;

    cout << "\nEnter Roll Number to search: ";
    cin >> targetRoll;

    inFile.open(FILENAME);
    if (!inFile) {
        cout << "Error: File could not be opened." << endl;
        return;
    }

    while (inFile >> s.rollNumber) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.grade);
        inFile >> s.marks;
        inFile.ignore();

        if (s.rollNumber == targetRoll) {
            cout << "\n--- Student Found ---" << endl;
            cout << "Roll No: " << s.rollNumber << endl;
            cout << "Name   : " << s.name << endl;
            cout << "Grade  : " << s.grade << endl;
            cout << "Marks  : " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << targetRoll << " not found." << endl;
    }
    inFile.close();
}

// 4. UPDATE STUDENT
void updateStudent() {
    int targetRoll;
    bool found = false;
    Student s;
    
    fstream inFile, tempFile;
    
    cout << "\nEnter Roll Number to update: ";
    cin >> targetRoll;

    inFile.open(FILENAME, ios::in);
    tempFile.open("temp.txt", ios::out); // Create a temporary file

    if (!inFile || !tempFile) {
        cout << "Error processing file." << endl;
        return;
    }

    while (inFile >> s.rollNumber) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.grade);
        inFile >> s.marks;
        inFile.ignore();

        if (s.rollNumber == targetRoll) {
            found = true;
            cout << "Record found! Enter new details:" << endl;
            
            // We keep the Roll Number same, or you can allow changing it too
            s.rollNumber = targetRoll; 
            
            cout << "Enter New Name: ";
            getline(cin >> ws, s.name); // 'ws' eats leading whitespace
            cout << "Enter New Grade: ";
            getline(cin, s.grade);
            cout << "Enter New Marks: ";
            cin >> s.marks;
        }

        // Write (either the old data or the updated data) to temp file
        tempFile << s.rollNumber << endl;
        tempFile << s.name << endl;
        tempFile << s.grade << endl;
        tempFile << s.marks << endl;
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(FILENAME.c_str());       // Delete original file
        rename("temp.txt", FILENAME.c_str()); // Rename temp to original
        cout << "Record updated successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Student not found." << endl;
    }
}

// 5. DELETE STUDENT
void deleteStudent() {
    int targetRoll;
    bool found = false;
    Student s;
    
    ifstream inFile;
    ofstream tempFile;

    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    inFile.open(FILENAME);
    tempFile.open("temp.txt");

    if (!inFile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    while (inFile >> s.rollNumber) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.grade);
        inFile >> s.marks;
        inFile.ignore();

        if (s.rollNumber == targetRoll) {
            found = true;
            cout << "Student with Roll " << targetRoll << " deleted." << endl;
            // We do NOT write this record to the temp file, effectively deleting it
        } else {
            // Write all other records to temp file
            tempFile << s.rollNumber << endl;
            tempFile << s.name << endl;
            tempFile << s.grade << endl;
            tempFile << s.marks << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(FILENAME.c_str());
        rename("temp.txt", FILENAME.c_str());
    } else {
        remove("temp.txt");
        cout << "Student not found." << endl;
    }
}

// Helper function for table header
void printHeader() {
    cout << "\n--------------------------------------------------" << endl;
    cout << left << setw(10) << "Roll No" 
         << setw(20) << "Name" 
         << setw(10) << "Grade" 
         << setw(10) << "Marks" << endl;
    cout << "--------------------------------------------------" << endl;
}
