/*
    You are given a file containing lines, each representing a point in the XY plane. 
    Each line consists of two floating-point numbers separated by a space, 
    representing the coordinates {x, y} of a point. 
    
    Write a C function that takes the input file as a parameter, processes each line, 
    and prints out the points in order based on their x value and on decreasing 
    order based on their y value.

    struct with x and y for a point
    read line from file with fscanf
    put into a dynamically allocated array of points
    sort points
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x, y;
}POINT;

typedef struct {
    POINT *points;
    unsigned number_of_points;
}PLANE;

PLANE make_space_for_new_point(PLANE plane) {
    ++plane.number_of_points;
    POINT *aux = realloc(plane.points, plane.number_of_points * sizeof(POINT));
    if(aux == NULL) {
        perror("Couldn't allocate enough space");
        exit(-1);
    }
    plane.points = aux;
    return plane;
}

PLANE make_plane_from_file(FILE *input) {
    PLANE plane = {NULL, 0};
    POINT point;

    while(fscanf(input, "%f %f", &point.x, &point.y) == 2) {
        plane = make_space_for_new_point(plane);
        plane.points[plane.number_of_points - 1] = point;
    }

    return plane;
}

void print_points(PLANE plane) {
    for(unsigned idx = 0; idx < plane.number_of_points; ++idx) {
        printf("POINT #%d: {%f, %f}\n", idx, plane.points[idx].x, plane.points[idx].y);
    }
}

int compare_points(const void* p1, const void *p2) {
    POINT *point1 = (POINT*)p1;
    POINT *point2 = (POINT*)p2;

    if(point1->x != point2->x) {
        return point1->x - point2->x;
    }
    else {
        return point2->y - point1->y;
    }
}

void print_points_in_order(FILE* input) {
    PLANE plane = make_plane_from_file(input);
    qsort(plane.points, plane.number_of_points, sizeof(POINT), compare_points);
    print_points(plane);
    free(plane.points);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage ./program <input_file>\n");
        exit(-1);
    }
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Error with opening file");
        exit(-1);
    }

    print_points_in_order(f);

    if(fclose(f) != 0) {
        perror("Error with closing file");
        exit(-1);
    }
    return 0;
}