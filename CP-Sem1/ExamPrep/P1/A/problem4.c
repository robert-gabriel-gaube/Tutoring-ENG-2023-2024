#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE_LEN 500

typedef struct {
    char name[11];
    int grades[10];
    int number_of_grades;
    float average;
}STUDENT;

typedef struct {
    STUDENT *students;
    int number_of_students;
}SCHOOL;

FILE *process_args(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage ./program <input_path>");
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Error while opening file.");
        exit(EXIT_FAILURE);
    }
    return f;
}
void close_file(FILE *f) {
    if(fclose(f) == EOF) {
        perror("Error while closing file");
        exit(EXIT_FAILURE);
    }
}
char *find_next_digit(char *s) {
    int number_of_positions = strcspn(s, "0123456789");
    return s + number_of_positions;
}

STUDENT process_line(char *line) {
    float sum = 0;

    STUDENT student;
    student.number_of_grades = 0;
    sscanf(line, "%[^:]s", student.name);

    char *end_number;
    line = find_next_digit(line);

    while(*line) {
        student.grades[student.number_of_grades] = strtol(line, &end_number, 10);
        sum += student.grades[student.number_of_grades];
        ++student.number_of_grades;
        line = find_next_digit(end_number);
    }

    student.average = sum / student.number_of_grades;

    return student;
}

SCHOOL make_space_for_student(SCHOOL school) {
    ++school.number_of_students;
    STUDENT *aux = realloc(school.students, school.number_of_students * sizeof(STUDENT));
    if(aux == NULL) {
        perror("Not enough space for alloc");
        exit(EXIT_FAILURE);
    }
    school.students = aux;
    return school;
}

SCHOOL read_lines(FILE *input) {
    SCHOOL school;

    char line[LINE_LEN];
    while(fgets(line, LINE_LEN, input)) {
        school = make_space_for_student(school);
        school.students[school.number_of_students - 1] = process_line(line);
    }

    return school;
}

int compare_students(const void *s1, const void *s2) {
    STUDENT *student1 = (STUDENT*)s1;
    STUDENT *student2 = (STUDENT*)s2; 

    if(student1->average != student2->average) {
        return student1->average - student2->average;
    } else {
        return strcmp(student1->name, student2->name);
    }
}

void print_students(SCHOOL school) {
    for(int idx = 0; idx < school.number_of_students; ++idx) {
        STUDENT student =  school.students[idx];
        printf("LINE #%d: %s: ", idx, student.name);
        for(int idx_g = 0; idx_g < student.number_of_grades - 1; ++idx_g) {
            printf("%d, ", student.grades[idx_g]);
        }
        printf("%d", student.grades[student.number_of_grades - 1]);
        printf(" with average: %f\n", student.average);
    }
}

void print_sorted(FILE *input) {
    SCHOOL school = read_lines(input);
    qsort(school.students, school.number_of_students, sizeof(STUDENT), compare_students);
    print_students(school);
}

int main(int argc, char *argv[]) {
    FILE *input = process_args(argc, argv);

    print_sorted(input);

    close_file(input);
    return 0;
}