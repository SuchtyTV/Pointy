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
    
    data.triangle = malloc(SPACE_FOR_RECTANGLES*sizeof(char*)); /*for the moment, make space for
                                                              SPACE_FOR_RECTANGLES */
    if(data.triangle != NULL){
        for(int i = 0; i < SPACE_FOR_RECTANGLES; i++){
            data.triangle[i] = calloc(MAX_DIGITS_RECT, 1);
            if(data.triangle[i] == NULL){
                fprintf(stderr, "Could not allocate enough memory to perform compilation.");
                return -1;
            }
        }
    } else {
        fprintf(stderr, "Could not allocate enough memory to perform compilation.");
        return -1;
    }
    
    data.bool_appended_triangel = 0; //Was a list already printed?
    data.bool_appended_points = 0; //Was a list already printed?
    data.numbers_written = 0; //counter
    data.points_index = (size_t)-1;
    data.triangel_index = (size_t)-1;
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
    printRectangleList(data.bool_appended_triangel, data.triangle, data.triangel_index);
    
    printBottom();
    
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
        printf("]\n\n");
    } else {
        printf("])\n\n");
    }
    appended = 1;
}

void printRectangleList(char appended, char** triangels, size_t index){
    if(!appended){
        printf("triangles =  [\n");
    } else {
        printf("triangles.extend(\n");
    }
    for(size_t i = 0; i <= index; i++){
        printf("%s,\n", triangels[i]);
    }
    if(!appended){
        printf("]\n\n");
    } else {
        printf("])\n\n");
    }
    appended = 1;
}

void setup(){
    printf("from mpl_toolkits.mplot3d import Axes3D\n");
    printf("import numpy as np\n\n");
    printf("from mpl_toolkits.mplot3d import Axes3D \n");
    printf("from itertools import chain \n");
    printf("import matplotlib.pyplot as plt\n\n");
    
    printf("zs = []\n");
    printf("xs = []\n");
    printf("ys = []\n\n");

    printf("fig = plt.figure()\n");
    printf("axrec = Axes3D(fig)\n");
    printf("ax = fig.add_subplot(111, projection='3d')\n\n");
    
    
}
void printBottom(){
    printf("for val in points:\n");
    printf("  (x,y,z) = val\n");
    printf("  xs.append(x)\n");
    printf("  ys.append(y)\n");
    printf("  zs.append(z)\n\n");
    
    printf("tri_points = list(chain.from_iterable(triangles))\n");
    printf("x, y, z = zip(*tri_points)\n");
    printf("tri_idx = [(3 * i, 3 * i + 1, 3 * i + 2) for i in range(len(triangles))]\n");
    printf("ax = plt.figure().gca(projection='3d')\n");
    printf("ax.plot_trisurf(x, y, z, triangles=tri_idx)\n\n");

    printf("ax.scatter(xs, ys, zs, marker='o')\n\n");
    printf("plt.show()");
}
