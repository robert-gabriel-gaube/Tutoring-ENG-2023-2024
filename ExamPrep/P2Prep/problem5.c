/*
    Read data from a file given as a command line argument. Every line 
    contains input in the following format: “student-name grade-average”. 
    The file is technically a student database. Read this file and print out 
    the students in decreasing order based on the grade-average. Break ties by 
    alphabetically sorting the students.

    Presume that a student's name is at most 50 characters.
    Presume that a line is at most 100 chars.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float grade_average;
}STUDENT;

typedef struct {
    STUDENT *students;
    unsigned number_of_students;
}STUDENT_REPO;

STUDENT_REPO process_file(FILE *input_file) {
    STUDENT student;
    STUDENT_REPO repo = {NULL, 0};
    
    while(fscanf(input_file, "%50s %f", student.name, &student.grade_average) == 2) {
        repo.number_of_students++;

        STUDENT *aux = realloc(repo.students, repo.number_of_students * sizeof(STUDENT));
        if(aux == NULL) {
            free(repo.students);
            exit(1);
        }
        repo.students = aux;

        repo.students[repo.number_of_students - 1] = student;
    }
    return repo;
}

int compare_students(const void *s1, const void *s2) {
    const STUDENT *student1 = (const STUDENT*)s1;
    const STUDENT *student2 = (const STUDENT*)s2;

    if(student1 -> grade_average != student2 -> grade_average) {
        if(student1 -> grade_average > student2 -> grade_average) {
            return -1;
        } else {
            return 1;
        }
    } else {
        return strcmp(student1 -> name, student2 -> name);
    }
}

void print_repo(STUDENT_REPO repo) {
    for(int i = 0; i < repo.number_of_students; ++i) {
        printf("Student #%d: name: %s, grade_avg: %f\n", i, repo.students[i].name, repo.students[i].grade_average);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage ./p <file_name>\n");
        exit(1);
    }

    FILE *input_file = fopen(argv[1], "r");
    if(input_file == NULL) {
        printf("Error while opening file\n");
        exit(1);
    }

    STUDENT_REPO repo = process_file(input_file);
    qsort(repo.students, repo.number_of_students, sizeof(STUDENT), compare_students);
    print_repo(repo);

    if(fclose(input_file) != 0) {
        printf("Error while closing file\n");
        exit(1);
    }

    return 0;
}
