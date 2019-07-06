#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>
#include "compilation.h"
#include "main.h"


int main(int argc, char * argv[]) {
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL)return errno;
    struct Data data;
    struct State state;
    state.lastletter = endparen;
    //Do parsing
    data.points = malloc(SPACE_FOR_POINTS * sizeof(char*)); //for the moment, make space for SPACE_FOR_POINTS
    if(data.points != NULL){
        for(int i = 0; i < SPACE_FOR_POINTS; i++){
            /*
             This is a point to be stored:
             (double,double,double)\0
             */
            data.points[i] = calloc(MAX_DIGITS_POINTS,1);
            
            if(data.points[i] == NULL){
                fprintf(stderr, "Could not allocate enough memory to perform compilation.");
                return -1;
            }
        }
    } else {
        fprintf(stderr, "Could not allocate enough memory to perform compilation.");
        return -1;
    }
    
    data.rectangles = malloc(SPACE_FOR_RECTANGLES*sizeof(char*)); /*for the moment, make space for
                                                              SPACE_FOR_RECTANGLES */
    if(data.rectangles != NULL){
        for(int i = 0; i < SPACE_FOR_RECTANGLES; i++){
            data.rectangles[i] = calloc(MAX_DIGITS_RECT, 1);
            if(data.rectangles[i] == NULL){
                fprintf(stderr, "Could not allocate enough memory to perform compilation.");
                return -1;
            }
        }
    } else {
        fprintf(stderr, "Could not allocate enough memory to perform compilation.");
        return -1;
    }
    
    data.bool_appended_rectangle = 0; //Was a list already printed?
    data.bool_appended_points = 0; //Was a list already printed?
    data.numbers_written = 0; //counter
    data.points_index = (size_t)-1;
    data.rectangels_index = (size_t)-1;
    data.actual_index = 0; //counter
    
    //Setting up
    setup();
    //State machine
    for (char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        if(isspace(ch)){
            continue;
        }
        compile(&state, &data, ch);
    }
    
    printPointList(data.bool_appended_points, data.points, data.points_index);
    printRectangleList(data.bool_appended_rectangle, data.rectangles, data.rectangels_index);
    
    printf("for val in points:\n");
    printf("  (x,y,z) = val\n");
    printf("  ax.scatter(x, y, z, marker='o')\n\n");
    
    printf("plt.show()");
    
    fclose(stdout); //needed?
    fclose(fp);
    return 1;
}

void printPointList(char appended, char** points, size_t index){
    if(!appended){
        printf("points =  [\n");
    } else {
        printf("points.extend(\n");
    }
    for(size_t i = 0; i <= index; i++){
        printf("%s,\n", points[i]);
    }
    if(!appended){
        printf("]\n");
    } else {
        printf("])\n");
    }
    appended = 1;
}

void printRectangleList(char appended, char** rectangles, size_t index){
    if(!appended){
        printf("rectangle =  [\n");
    } else {
        printf("rectangle.extend(\n");
    }
    for(size_t i = 0; i <= index; i++){
        printf("%s,\n", rectangles[i]);
    }
    if(!appended){
        printf("]\n");
    } else {
        printf("])\n");
    }
    appended = 1;
}

void setup(){
    printf("from mpl_toolkits.mplot3d import Axes3D\n");
    printf("import matplotlib.pyplot as plt\n");
    printf("import numpy as np\n\n");
    printf("fig = plt.figure()\n");
    printf("ax = fig.add_subplot(111, projection='3d')\n\n");
}
