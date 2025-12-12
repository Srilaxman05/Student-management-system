# Student Management System (C++)

A comprehensive console-based application to manage student records. This system uses **C++** and **File Handling** to perform **CRUD** (Create, Read, Update, Delete) operations, ensuring data persists in a text file even after the program closes.

## 🚀 Features

- **Add Student**: Store Roll Number, Name, Grade, and Marks.
- **Display All**: View all student records formatted in a neat table.
- **Search**: Find specific students by their Roll Number.
- **Update**: Modify details of an existing student (Name, Grade, Marks).
- **Delete**: Remove a student record permanently.
- **Data Persistence**: Uses a text file (`student_data.txt`) to save data automatically.

## 🛠️ Technology Stack

- **Language**: C++ (Standard Library)
- **Concepts**: File Handling (`fstream`), Structures (`struct`), Logic (Loops/Switch).

## 💻 How to Run

### 1. Compile the Code
Open your terminal or command prompt in the project folder and run:

    g++ main.cpp -o student_system

### 2. Execute
**On Windows:**

    student_system.exe

**On Linux / Mac:**

    ./student_system

## 📂 File Structure

    ├── main.cpp          # The source code
    ├── student_data.txt  # Generated automatically to store records
    └── README.md         # Project documentation

## ⚙️ How It Works (Internal Logic)

1. **Storage**: Data is stored in `student_data.txt`. Each field (Roll, Name, Grade, Marks) takes up one line.
2. **Update/Delete**: Since text files cannot be modified in the middle easily, the system uses a **Temp File** approach:
   - It reads the original file.
   - Writes all records *except* the modified/deleted one to `temp.txt`.
   - Deletes the original file and renames `temp.txt` to `student_data.txt`.

## 🔮 Future Improvements

- Implement input validation (e.g., prevent entering letters for marks).
- Add authentication (Login/Password) for the admin.
- Sort students by marks or name.

---
*Created by Srilaxman.EU*
