# Student Academic Management - BUT Computer Science (SAÉ S1.01)

This project was developed as part of the **SAÉ S1.01: Implementation of a Client Need** at the IUT of Paris - Rives de Seine (Université Paris Cité).

The objective is to develop a **C language application** to manage the academic records of a cohort of Computer Science students (Bachelor of Technology) using a command-line interpreter.

## 📋 Features

The program functions as an interpreter that reads commands from standard input and outputs results to standard output. It complies with the official academic rules of the degree (module validation, compensation, juries, and progression to the next year).

The application manages:
* **Students**: Registration, resignation, and academic failure.
* **Grades**: Recording grades (0-20) for the 6 teaching units (UE) of each semester.
* **Transcripts**: Displaying academic records, calculating averages (RCUE), and assigning decision codes (ADM, AJ, ADC, etc.).
* **Juries**: Automatic validation for odd semesters and deliberation logic for even semesters (pass or fail).
* **Reports**: Generating annual statistical summaries for the cohort.

## 🛠️ Supported Commands

The project interprets the following 9 commands.
*> Note: The keywords must be typed in French as specified by the project requirements.*

| Command Keyword | Usage | Description |
| :--- | :--- | :--- |
| `INSCRIRE` | `INSCRIRE <Firstname> <Lastname>` | Registers a new student (Max 100). |
| `NOTE` | `NOTE <Id> <UE> <Grade>` | Records a grade for a specific Teaching Unit (UE). |
| `CURSUS` | `CURSUS <Id>` | Displays the complete academic transcript and status of a student. |
| `DEMISSION` | `DEMISSION <Id>` | Marks a student as resigned. |
| `DEFAILLANCE` | `DEFAILLANCE <Id>` | Marks a student as failing (due to unexcused absences). |
| `JURY` | `JURY <Semester>` | Executes the jury process for a given semester (1 to 6). |
| `ETUDIANTS` | `ETUDIANTS` | Lists all students and their current status. |
| `BILAN` | `BILAN <Year>` | Displays the statistical report for a specific year (1, 2, or 3). |
| `EXIT` | `EXIT` | Terminates the program. |

## 💻 Technical Specifications

* **Language**: C
* **Data Structure**: Usage of `struct` for students and promotion management to optimize memory usage.
* **Constraints**: Supports up to 100 students; First/Last names limited to 30 characters.
* **Precision**: Grades are stored as `float` but displayed with one decimal place truncated (no rounding).

## 🚀 Installation and Usage

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/student-management-but.git](https://github.com/your-username/student-management-but.git)
