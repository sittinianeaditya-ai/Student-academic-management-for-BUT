#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Disable specific warnings for Visual Studio (unsafe functions like scanf, strcpy)
#pragma warning(disable:4996 6031)

// --- CONSTANTS AND CONFIGURATION ---
enum {
    MAX_STUDENTS = 100,
    NB_COURSES = 6,      // Number of courses (UE) per semester
    NB_SEMESTERS = 6,    // Total semesters (L1, L2, L3)
    NB_YEARS = 3,        // Total years
    MAX_NAME = 31,
    MAX_STATUS = 16,
    MIN_VALID_YEAR_AVG = 4 // Minimum number of validated courses required to pass a year
};

// Grading thresholds
const float GRADE_MIN = 0.0f;
const float GRADE_MAX = 20.0f;
const float GRADE_UNKNOWN = -1.0f;
const float PASS_THRESHOLD = 10.0f;     // Grade needed to pass (10/20)
const float FAIL_LOW_THRESHOLD = 8.0f;  // "Note éliminatoire" (AJB)

// --- DATA STRUCTURES ---

// Structure for a single course grade (UE)
typedef struct {
    float grade;
    char code[4]; // Status code: PAS (ADM), FAI (AJ), etc.
} CourseGrade;

// Structure for the Yearly Average of a course (RCUE)
// Calculated as average of Semester Odd + Semester Even for the same course index
typedef struct {
    float grade;
    char code[4];
} YearAvg;

// Main Student Structure
typedef struct {
    int ID;
    char FIRST_NAME[MAX_NAME];
    char LAST_NAME[MAX_NAME];

    // Matrix of grades: [Semester 0-5][Course 0-5]
    CourseGrade SEMESTER_GRADES[NB_SEMESTERS][NB_COURSES];

    // Matrix of yearly averages: [Year 0-2][Course 0-5]
    YearAvg YEARLY_RESULTS[NB_YEARS][NB_COURSES];

    int current_semester;    // Index of the current semester (0 to 5)
    char STATUS[MAX_STATUS]; // "in progress", "failed", "graduated", etc.
} Student;

// Helper function to truncate grades to 1 decimal place (e.g., 10.59 -> 10.5)
float truncateGrade(float grade) {
    return floorf(grade * 10.0f) / 10.0f;
}

// --- COMMAND: REGISTER (INSCRIRE) ---
// Adds a new student to the system
void REGISTER(Student students[], int* nb_stu, char FIRST_NAME[], char LAST_NAME[]) {
    // 1. Check for duplicates
    for (int i = 0; i < *nb_stu; ++i) {
        if (strcmp(students[i].FIRST_NAME, FIRST_NAME) == 0 && strcmp(students[i].LAST_NAME, LAST_NAME) == 0) {
            printf("Incorrect name\n"); // Means "Already exists" in this context
            return;
        }
    }

    // 2. Check capacity
    if (*nb_stu >= MAX_STUDENTS) {
        printf("Maximum number of students reached\n");
        return;
    }

    // 3. Initialize new student
    Student* new_stu = &students[*nb_stu];
    new_stu->ID = (*nb_stu) + 1;
    strcpy(new_stu->FIRST_NAME, FIRST_NAME);
    strcpy(new_stu->LAST_NAME, LAST_NAME);
    new_stu->current_semester = 0; // Starts at Semester 1 (index 0)
    strcpy(new_stu->STATUS, "in progress");

    // Initialize all grades to UNKNOWN (*)
    for (int s = 0; s < NB_SEMESTERS; ++s) {
        for (int c = 0; c < NB_COURSES; ++c) {
            new_stu->SEMESTER_GRADES[s][c].grade = GRADE_UNKNOWN;
            strcpy(new_stu->SEMESTER_GRADES[s][c].code, "*");
        }
    }
    for (int y = 0; y < NB_YEARS; ++y) {
        for (int c = 0; c < NB_COURSES; ++c) {
            new_stu->YEARLY_RESULTS[y][c].grade = GRADE_UNKNOWN;
            strcpy(new_stu->YEARLY_RESULTS[y][c].code, "*");
        }
    }

    (*nb_stu)++;
    printf("Registration recorded (%d)\n", new_stu->ID);
}

// --- COMMAND: GRADE (NOTE) ---
// Assigns a grade to a specific course for the student's *current* semester
void GRADE(Student students[], int nb_stu, int id, int course, float grade) {
    // Basic validation
    if (id <= 0 || id > nb_stu) {
        printf("Incorrect identifier\n");
        return;
    }
    Student* stu = &students[id - 1];

    if (strcmp(stu->STATUS, "in progress") != 0) {
        printf("Student not in training\n");
        return;
    }

    if (course < 1 || course > NB_COURSES) {
        printf("Incorrect course\n");
        return;
    }
    if (grade < GRADE_MIN || grade > GRADE_MAX) {
        printf("Incorrect grade\n");
        return;
    }

    // Set the grade for the current semester
    int current_sem = stu->current_semester;
    int course_idx = course - 1;

    stu->SEMESTER_GRADES[current_sem][course_idx].grade = grade;
    strcpy(stu->SEMESTER_GRADES[current_sem][course_idx].code, "*"); // Reset code to default

    printf("Grade recorded\n");
}

// --- COMMAND: TRANSCRIPT (CURSUS) ---
// Displays the full academic history of a student
void TRANSCRIPT(Student students[], int nb_stu, int id) {
    if (id <= 0 || id > nb_stu) {
        printf("Incorrect identifier\n");
        return;
    }
    Student* stu = &students[id - 1];

    printf("%d %s %s\n", stu->ID, stu->FIRST_NAME, stu->LAST_NAME);

    // Loop through all semesters the student has started
    for (int s = 0; s <= stu->current_semester; ++s) {
        printf("S%d", s + 1);

        for (int c = 0; c < NB_COURSES; ++c) {
            CourseGrade* c_grade = &stu->SEMESTER_GRADES[s][c];

            if (c_grade->grade == GRADE_UNKNOWN) {
                printf(" - * (*)");
            }
            else {
                char display_code[4];
                // If the Jury hasn't run yet (code is "*"), simulate display
                if (strcmp(c_grade->code, "*") == 0) {
                    if (c_grade->grade >= PASS_THRESHOLD) strcpy(display_code, "PAS");
                    else strcpy(display_code, "FAI");
                }
                else {
                    strcpy(display_code, c_grade->code);
                }
                printf(" - %.1f (%s)", truncateGrade(c_grade->grade), display_code);
            }
        }

        printf(" -");

        // Print status only on the last line or if status is final
        int is_last_sem = (s == stu->current_semester);
        int is_final_stat = (strcmp(stu->STATUS, "failed") == 0 || strcmp(stu->STATUS, "graduated") == 0);

        if (is_last_sem && !is_final_stat) {
            printf(" %s\n", stu->STATUS);
        }
        else {
            printf("\n");
        }

        // If it was an even semester (S2, S4, S6), print the Year Summary (Bilan/RCUE)
        if (s % 2 != 0) {
            int year_idx = s / 2;
            // Only print if calculated
            if (strcmp(stu->YEARLY_RESULTS[year_idx][0].code, "*") != 0) {
                printf("Y%d", year_idx + 1);

                for (int c = 0; c < NB_COURSES; ++c) {
                    YearAvg* y_avg = &stu->YEARLY_RESULTS[year_idx][c];
                    printf(" - %.1f (%s)", truncateGrade(y_avg->grade), y_avg->code);
                }

                printf(" -");

                if (is_last_sem && is_final_stat) {
                    printf(" %s\n", stu->STATUS);
                }
                else {
                    printf("\n");
                }
            }
        }
    }
}

// --- COMMAND: STUDENTS (ETUDIANTS) ---
// Lists all students
void STUDENTS(Student students[], int nb_stu) {
    for (int i = 0; i < nb_stu; ++i) {
        printf("%d - %s %s - S%d - %s\n",
            students[i].ID,
            students[i].FIRST_NAME,
            students[i].LAST_NAME,
            students[i].current_semester + 1,
            students[i].STATUS);
    }
}

// --- ADMINISTRATIVE COMMANDS ---
void RESIGNATION(Student students[], int nb_stu, int id) {
    if (id <= 0 || id > nb_stu) {
        printf("Incorrect identifier\n");
        return;
    }
    Student* stu = &students[id - 1];

    if (strcmp(stu->STATUS, "in progress") != 0) {
        printf("Student not in training\n");
        return;
    }

    strcpy(stu->STATUS, "resigned");
    printf("Resignation recorded\n");
}

void FAILURE(Student students[], int nb_stu, int id) {
    if (id <= 0 || id > nb_stu) {
        printf("Incorrect identifier\n");
        return;
    }
    Student* stu = &students[id - 1];

    if (strcmp(stu->STATUS, "in progress") != 0) {
        printf("Student not in training\n");
        return;
    }

    strcpy(stu->STATUS, "defaulted"); // "Défaillance"
    printf("Default recorded\n");
}


// --- COMMAND: JURY (CORE LOGIC) ---
// Validates grades, calculates averages, applies compensation, and determines passage.
void JURY(Student students[], int nb_stu, int semester) {
    if (semester < 1 || semester > NB_SEMESTERS) {
        printf("Incorrect semester\n");
        return;
    }
    int sem_idx = semester - 1;

    // 1. Check if all grades are present for students in this semester
    int concerned_students = 0;
    for (int i = 0; i < nb_stu; ++i) {
        Student* stu = &students[i];

        if (stu->current_semester == sem_idx && strcmp(stu->STATUS, "in progress") == 0) {
            for (int c = 0; c < NB_COURSES; ++c) {
                if (stu->SEMESTER_GRADES[sem_idx][c].grade == GRADE_UNKNOWN) {
                    printf("Grades are missing\n");
                    return;
                }
            }
            concerned_students++;
        }
    }

    if (concerned_students == 0) {
        printf("Semester finished for 0 student(s)\n");
        return;
    }

    // 2. Process each student
    for (int i = 0; i < nb_stu; ++i) {
        Student* stu = &students[i];

        if (stu->current_semester == sem_idx && strcmp(stu->STATUS, "in progress") == 0) {

            // --- CASE A: Odd Semesters (S1, S3, S5) ---
            // Logic: Simple Pass/Fail check. No yearly average calculated yet.
            if (semester % 2 != 0) {
                for (int c = 0; c < NB_COURSES; ++c) {
                    CourseGrade* c_grade = &stu->SEMESTER_GRADES[sem_idx][c];
                    if (c_grade->grade >= PASS_THRESHOLD) {
                        strcpy(c_grade->code, "PAS"); // ADM
                    }
                    else {
                        strcpy(c_grade->code, "FAI"); // AJ
                    }
                }
                // Odd semesters always lead to the next semester (no blocking here in this model)
                if (sem_idx < NB_SEMESTERS - 1) {
                    stu->current_semester++;
                }
            }
            // --- CASE B: Even Semesters (S2, S4, S6) ---
            // Logic: Calculate Yearly Average (RCUE) = (S_Odd + S_Even) / 2
            else {
                int year_idx = sem_idx / 2;
                int nb_pass_avg = 0; // Count of validated yearly courses (RCUE)
                int has_low_fail = 0; // Flag for "Note éliminatoire" (AJB)

                for (int c = 0; c < NB_COURSES; ++c) {
                    CourseGrade* odd_course = &stu->SEMESTER_GRADES[sem_idx - 1][c];
                    CourseGrade* even_course = &stu->SEMESTER_GRADES[sem_idx][c];
                    YearAvg* y_avg = &stu->YEARLY_RESULTS[year_idx][c];

                    // Calculate Yearly Average for this course
                    y_avg->grade = (odd_course->grade + even_course->grade) / 2.0f;

                    // Compensation Logic
                    if (y_avg->grade >= PASS_THRESHOLD) {
                        strcpy(y_avg->code, "PAS");
                        nb_pass_avg++;

                        // If the year average is good, individual semesters are validated by Compensation (CMP)
                        if (odd_course->grade < PASS_THRESHOLD) strcpy(odd_course->code, "CMP"); // ADC
                        else strcpy(odd_course->code, "PAS");

                        if (even_course->grade < PASS_THRESHOLD) strcpy(even_course->code, "CMP"); // ADC
                        else strcpy(even_course->code, "PAS");

                    }
                    else {
                        // Yearly average failed
                        if (odd_course->grade >= PASS_THRESHOLD) strcpy(odd_course->code, "PAS");
                        else strcpy(odd_course->code, "FAI");

                        if (even_course->grade >= PASS_THRESHOLD) strcpy(even_course->code, "PAS");
                        else strcpy(even_course->code, "FAI");

                        // Check for Critical Failure (AJB / LOW)
                        if (y_avg->grade < FAIL_LOW_THRESHOLD) {
                            strcpy(y_avg->code, "LOW");
                            has_low_fail = 1;
                        }
                        else {
                            strcpy(y_avg->code, "FAI");
                        }
                    }
                }

                // --- Retroactive Validation (ADS/REC) ---
                // If current year passes, check if it can validate previous year's failed modules
                if (year_idx > 0) {
                    int prev_year = year_idx - 1;
                    for (int c = 0; c < NB_COURSES; ++c) {
                        // If current year course is passed
                        if (strcmp(stu->YEARLY_RESULTS[year_idx][c].code, "PAS") == 0) {
                            // And previous year same course was failed
                            if (strcmp(stu->YEARLY_RESULTS[prev_year][c].code, "FAI") == 0) {
                                strcpy(stu->YEARLY_RESULTS[prev_year][c].code, "REC"); // ADS (Admis Subséquent)

                                // Update the semesters of the previous year
                                int s_odd_prev = prev_year * 2;
                                int s_even_prev = prev_year * 2 + 1;

                                if (strcmp(stu->SEMESTER_GRADES[s_odd_prev][c].code, "FAI") == 0)
                                    strcpy(stu->SEMESTER_GRADES[s_odd_prev][c].code, "REC");

                                if (strcmp(stu->SEMESTER_GRADES[s_even_prev][c].code, "FAI") == 0)
                                    strcpy(stu->SEMESTER_GRADES[s_even_prev][c].code, "REC");
                            }
                        }
                    }
                }

                // --- Progression Decision ---
                int passed = 0;

                // Decision for Year 1 (S2) or Year 2 (S4)
                if (sem_idx == 1 || sem_idx == 3) {
                    // Condition 1: Enough validated courses this year AND no critical fail
                    int year_success = (nb_pass_avg >= MIN_VALID_YEAR_AVG) && !has_low_fail;

                    if (sem_idx == 1) {
                        // End of Year 1: Only need year success
                        passed = year_success;
                    }
                    else {
                        // End of Year 2: Need Year 2 success AND Year 1 fully valid
                        int y1_valid = 1;
                        for (int c = 0; c < NB_COURSES; ++c) {
                            char* code_s1 = stu->SEMESTER_GRADES[0][c].code;
                            char* code_s2 = stu->SEMESTER_GRADES[1][c].code;

                            // Check if S1 and S2 contain any unvalidated failures
                            if ((strcmp(code_s1, "PAS") != 0 && strcmp(code_s1, "CMP") != 0 && strcmp(code_s1, "REC") != 0) ||
                                (strcmp(code_s2, "PAS") != 0 && strcmp(code_s2, "CMP") != 0 && strcmp(code_s2, "REC") != 0))
                            {
                                y1_valid = 0;
                                break;
                            }
                        }
                        passed = year_success && y1_valid;
                    }
                }
                // Decision for Year 3 (S6) - Graduation
                else if (sem_idx == 5) {
                    int all_valid = 1;
                    // Check entire curriculum
                    for (int s = 0; s < NB_SEMESTRES; ++s) {
                        for (int c = 0; c < NB_COURSES; ++c) {
                            char* code_c = stu->SEMESTER_GRADES[s][c].code;
                            // Must be Passed, Compensated, or Recovered
                            if (strcmp(code_c, "PAS") != 0 &&
                                strcmp(code_c, "CMP") != 0 &&
                                strcmp(code_c, "REC") != 0) {
                                all_valid = 0;
                                break;
                            }
                        }
                        if (!all_valid) break;
                    }
                    passed = all_valid;
                }

                // Apply status based on decision
                if (passed) {
                    if (sem_idx == 5) {
                        strcpy(stu->STATUS, "graduated"); // DIPLOME
                    }
                    else {
                        stu->current_semester++; // Move to next semester (S3 or S5)
                    }
                }
                else {
                    strcpy(stu->STATUS, "failed"); // AJOURNE
                }
            }
        }
    }

    printf("Semester finished for %d student(s)\n", concerned_students);
}

// --- COMMAND: REPORT (BILAN) ---
// Statistical summary of student statuses for a given year
void REPORT(Student students[], int nb_stu, int year) {
    if (year < 1 || year > 3) {
        printf("Incorrect year\n");
        return;
    }

    int resignations = 0;
    int defaults = 0;
    int in_progress = 0;
    int failed = 0;
    int passed = 0;

    int year_idx = year - 1;
    int s_odd_idx = year_idx * 2;
    int s_even_idx = year_idx * 2 + 1;

    for (int i = 0; i < nb_stu; ++i) {
        Student* stu = &students[i];

        // Skip students who haven't reached this year yet
        if (stu->current_semester < s_odd_idx) {
            continue;
        }

        // Count based on status and where they stopped
        if (strcmp(stu->STATUS, "resigned") == 0) {
            if (stu->current_semester == s_odd_idx || stu->current_semester == s_even_idx) {
                resignations++;
            }
        }
        else if (strcmp(stu->STATUS, "defaulted") == 0) {
            if (stu->current_semester == s_odd_idx || stu->current_semester == s_even_idx) {
                defaults++;
            }
        }
        else if (strcmp(stu->STATUS, "in progress") == 0) {
            if (stu->current_semester == s_odd_idx || stu->current_semester == s_even_idx) {
                in_progress++;
            }
        }
        else if (strcmp(stu->STATUS, "failed") == 0) {
            // Failed students are stuck at the even semester of that year
            if (stu->current_semester == s_even_idx) {
                failed++;
            }
        }
        else if (strcmp(stu->STATUS, "graduated") == 0) {
            if (year == 3 && stu->current_semester == s_even_idx) {
                passed++;
            }
        }

        // Students who have moved past this year are considered "passed" for this year
        if (stu->current_semester > s_even_idx) {
            passed++;
        }
    }

    printf("%d resignation(s)\n", resignations);
    printf("%d default(s)\n", defaults);
    printf("%d in progress\n", in_progress);
    printf("%d failed\n", failed);
    printf("%d passed\n", passed);
}

// --- MAIN FUNCTION ---
int main() {
    Student promotion_students[MAX_STUDENTS];
    int nb_stu = 0;
    char cmd[MAX_NAME] = "";

    // Command loop
    do {
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "REGISTER") == 0) {
            char first_name[MAX_NAME], last_name[MAX_NAME];
            scanf("%s %s", first_name, last_name);
            REGISTER(promotion_students, &nb_stu, first_name, last_name);
        }
        else if (strcmp(cmd, "GRADE") == 0) {
            int id, course;
            float grade;
            scanf("%d %d %f", &id, &course, &grade);
            GRADE(promotion_students, nb_stu, id, course, grade);
        }
        else if (strcmp(cmd, "TRANSCRIPT") == 0) {
            int id;
            scanf("%d", &id);
            TRANSCRIPT(promotion_students, nb_stu, id);
        }
        else if (strcmp(cmd, "STUDENTS") == 0) {
            STUDENTS(promotion_students, nb_stu);
        }
        else if (strcmp(cmd, "RESIGNATION") == 0) {
            int id;
            scanf("%d", &id);
            RESIGNATION(promotion_students, nb_stu, id);
        }
        else if (strcmp(cmd, "FAILURE") == 0) {
            int id;
            scanf("%d", &id);
            FAILURE(promotion_students, nb_stu, id);
        }
        else if (strcmp(cmd, "JURY") == 0) {
            int semester;
            scanf("%d", &semester);
            JURY(promotion_students, nb_stu, semester);
        }
        else if (strcmp(cmd, "REPORT") == 0) {
            int year;
            scanf("%d", &year);
            REPORT(promotion_students, nb_stu, year);
        }

    } while (strcmp(cmd, "EXIT") != 0);

    return 0;
}