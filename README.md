# Student Management System

A comprehensive console-based application to manage student records. This system uses C++ file handling to perform **CRUD** (Create, Read, Update, Delete) operations, ensuring data persists in a text file even after the program closes.

## 🚀 Features
- **Add Student**: Store Roll No, Name, Grade, and Marks.
- **Display All**: View all student records formatted in a table.
- **Search**: Find specific students by their Roll Number.
- **Update**: Modify details of an existing student.
- **Delete**: Remove a student record permanently.
- **Data Persistence**: Uses `student_data.txt` to save data automatically.

## 🛠️ Technologies Used
- **Language**: C++
- **Concepts**: File Handling (`fstream`), Structures, Loops, Switch-Case.

## 💻 How to Run

### 1. Compile the Code
Open your terminal or command prompt and run:
```bash
g++ main.cpp -o student_system
