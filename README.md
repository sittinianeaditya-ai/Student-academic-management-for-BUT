# Student Academic Management - BUT Computer Science (SAÉ S1.01)

[cite_start]This project was developed as part of the **SAÉ S1.01: Implementation of a Client Need** at the IUT of Paris - Rives de Seine (Université Paris Cité)[cite: 1, 3].

[cite_start]The objective is to develop a **C language application** to manage the academic records of a cohort of Computer Science students (Bachelor of Technology) using a command-line interpreter[cite: 5].

## 📋 Features

[cite_start]The program functions as an interpreter that reads commands from standard input and outputs results to standard output[cite: 29]. [cite_start]It complies with the official academic rules of the degree (module validation, compensation, juries, and progression to the next year)[cite: 11, 15].

The application manages:
* [cite_start]**Students**: Registration, resignation, and academic failure[cite: 34, 89].
* [cite_start]**Grades**: Recording grades (0-20) for the 6 teaching units (UE) of each semester[cite: 9, 68].
* [cite_start]**Transcripts**: Displaying academic records, calculating averages (RCUE), and assigning decision codes (ADM, AJ, ADC, etc.)[cite: 10, 87].
* [cite_start]**Juries**: Automatic validation for odd semesters and deliberation logic for even semesters (pass or fail)[cite: 18, 19].
* [cite_start]**Reports**: Generating annual statistical summaries for the cohort[cite: 428].

## 🛠️ Supported Commands

The project interprets the following 9 commands.
*> Note: The keywords must be typed in French as specified by the project requirements.*

| Command Keyword | Usage | Description |
| :--- | :--- | :--- |
| `INSCRIRE` | `INSCRIRE <Firstname> <Lastname>` | [cite_start]Registers a new student (Max 100)[cite: 34, 450]. |
| `NOTE` | `NOTE <Id> <UE> <Grade>` | [cite_start]Records a grade for a specific Teaching Unit (UE)[cite: 67]. |
| `CURSUS` | `CURSUS <Id>` | [cite_start]Displays the complete academic transcript and status of a student[cite: 46]. |
| `DEMISSION` | `DEMISSION <Id>` | [cite_start]Marks a student as resigned[cite: 90]. |
| `DEFAILLANCE` | `DEFAILLANCE <Id>` | [cite_start]Marks a student as failing (due to unexcused absences)[cite: 90]. |
| `JURY` | `JURY <Semester>` | [cite_start]Executes the jury process for a given semester (1 to 6)[cite: 106]. |
| `ETUDIANTS` | `ETUDIANTS` | [cite_start]Lists all students and their current status[cite: 411]. |
| `BILAN` | `BILAN <Year>` | [cite_start]Displays the statistical report for a specific year (1, 2, or 3)[cite: 429]. |
| `EXIT` | `EXIT` | [cite_start]Terminates the program[cite: 32]. |

## 💻 Technical Specifications

* **Language**: C
* [cite_start]**Data Structure**: Usage of `struct` for students and promotion management to optimize memory usage[cite: 892, 901].
* **Constraints**: Supports up to 100 students; [cite_start]First/Last names limited to 30 characters[cite: 450].
* [cite_start]**Precision**: Grades are stored as `float` but displayed with one decimal place truncated (no rounding)[cite: 452, 455].

## 🚀 Installation and Usage

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/student-management-but.git](https://github.com/your-username/student-management-but.git)
