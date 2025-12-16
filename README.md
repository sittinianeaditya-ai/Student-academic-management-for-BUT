Here is the cleaned-up content, ready to be copied into your `README.md` file:

#Student Management - Computer Science Bachelor of Technology (SAÉ S1.01) This project was carried out as part of **SAÉ S1.01: Implementation of a Client Need** at the IUT of Paris - Rives de Seine (Paris Cité University).

The objective is to develop a C** application to manage the academic records of a cohort of Computer Science Bachelor of Technology students using a command interpreter.

##📋 Features The program functions as an interpreter that reads commands from standard input and outputs the results to standard output. It complies with the official management rules of the Bachelor of Technology (validation of modules, compensation, juries, progression to the next year).

The application manages:

* **Students**: Registration, withdrawal, failure.

* **Grades**: Enter grades (0-20) for the 6 modules of each semester.

* **Course Record**: Display the transcript, calculate averages (RCUE), and display decision codes (ADM, AJ, ADC, etc.).

* **Examination Panels**: Automatic validation of odd-numbered semesters and deliberation for even-numbered semesters (pass or fail).

* **Summary**: Annual statistics for the graduating class.

##🛠️ Supported Commands The project interprets the following 9 commands:

| Command | Action |

| --- | --- |

| `REGISTER First Name Last Name` | Registers a new student (max 100). |

| `GRADE Module ID Grade` | Records a grade for a given module. |

| `COURSE ID` | Displays the complete academic record and status of a student. |

| `RESIGN ID` | Record a student's resignation. |

| `DEFAILLANCE Id` | Record a failure (unexcused absences). |

| `JURY Semester` | Starts the jury for a given semester (1 to 6). |

| `STUDENTS` | Displays the list of all students and their status. |

| `Year REPORT` | Displays the statistical report for a year (1, 2, or 3). |

| `EXIT` | Exits the program. |

##💻 Technical Specifications* **Language**: C
* **Data Structure**: Uses `struct` for students and year groups to optimize memory.

* **Limitations**: Supports up to 100 students, first/last names limited to 30 characters.

* **Accuracy**: Grades are stored as `float` but displayed with one truncated decimal place.

##🚀 Installation and Usage 1. **Clone the repository:**
```bash
git clone https://github.com/your-name/gestion-scolarite-but.git

```

2. **Compile the project:**
```bash
gcc main.c -o gestion_scolarite

```

3. **Run the program:**
```bash
./gestion_scolarite

```

###Tests The project has been validated using the provided test suites (`in.txt` and `out.txt`). You can test the program by redirecting standard input:

```bash
./gestion_scolarite < in.txt > resultat.txt
diff resultat.txt out.txt

```
