#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct student {
    char name[51];
    float grades[10];
    int no_grades;
    float avg_grade;
    int passing_grades;
}STUDENT;

void print_student(STUDENT s) {
    printf("NAME: %s\n", s.name);
    printf("NUM_GRADES: %d\n", s.no_grades);
    printf("GRADES:\n");
    for(int idx = 0; idx < s.no_grades; ++idx) {
        printf("\t %d: %f\n", idx, s.grades[idx]);
    }
    printf("NUMBER_PASSING_GRADES: %d\n", s.passing_grades);
    printf("AVERAGE_GRADE: %f\n", s.avg_grade);
    printf("\n\n");
}

void print_students(STUDENT *students, int num_students) {
    for(int i = 0; i < num_students; ++i) {
        print_student(students[i]);
    }
}

/*
    Plan:
        1. Process csv line into STUDENT
        2. Process all lines into an array 
        3. Sort students based on criteria
*/

// 1. Process csv line into STUDENT
// Regex stuff, view course
// fscanf(f, "%50[^,]s", student.name);
STUDENT process_line(char *line) {
    // Initialize struct and it's fields
    STUDENT student;
    student.no_grades = 0;
    student.passing_grades = 0;

    // Reading name
    int idx = 0;
    while(line[idx] != ',') {
        student.name[idx] = line[idx];
        idx++;
    }
    student.name[idx] = '\0';

    // Reading grades
    // Jump over name
    char *pointer = line + idx;
    float sum = 0;

    // First strtok to be used with pointer to char 
    pointer = strtok(pointer, ",");
    while(pointer) {
        // Convert to float
        float grade = strtof(pointer, NULL);
        sum += grade;

        // Store grade
        student.grades[student.no_grades] = grade;

        // Increment variables
        student.no_grades++;
        if(grade >= 5) student.passing_grades++;

        // Go to next number (Consecutive strtok to be used with NULL)
        pointer = strtok(NULL, ",");
    }
    // Store average
    if (student.passing_grades < 5) {
        student.avg_grade = 0;
    } else {
        student.avg_grade = sum / student.no_grades;
    }

    return student;
}

// 2. Process all lines into an array 
// Return number of students read
int read_lines(FILE *f, STUDENT *students) {
    char line[500];
    int idx = 0;

    while(fgets(line, 500, f)) {
        students[idx] = process_line(line);
        idx++;
    }

    return idx;
}

FILE *open_file(const char *path) {
    FILE *f = fopen(path, "r");
    if(f == NULL) {
        perror("Error on opening file");
        exit(1);
    }
    return f;
}

int compare_students(const void *a, const void *b) {
    // Cast a and b to STUDENT* and then extract avg_grade from them
    float avg_grade_a = ((STUDENT*)a) -> avg_grade;
    float avg_grade_b = ((STUDENT*)b) -> avg_grade;
    
    // Cast a and b to STUDENT* and then extract name from them
    char *name_a = ((STUDENT*)a) -> name;
    char *name_b = ((STUDENT*)b) -> name;

    // If avg is different sort based on that
    if(avg_grade_a != avg_grade_b) {
        return avg_grade_b - avg_grade_a;
    }
    else {
        // If average is the same sort based on name
        return strcmp(name_a, name_b);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }
    FILE *input_csv = open_file(argv[1]);

    STUDENT students[200];
    int num_students = read_lines(input_csv, students);

    // Sort students

    qsort(students, num_students, sizeof(STUDENT), compare_students);

    print_students(students, num_students);

    if(fclose(input_csv) != 0) {
        perror("Error with closing file");
        exit(1);
    }


    return 0;
}