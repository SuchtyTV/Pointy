//  Created by Niclas Schwalbe on 05.07.19.
//  Copyright © 2019 Niclas Schwalbe. All rights reserved.

#ifndef compilation_h
#define compilation_h

#include <stdio.h>

struct State {
    enum{name, openparen, comma, number, endparen, error} lastletter;
    enum{point, rectangle} shape;
};

struct Data {
    char** points; //all future points will be stored here
    char** triangle; //all future regtangles will be stored here
    char bool_appended_triangel; //Was a list already printed?
    char bool_appended_points; //Was a list already printed?
    int numbers_written; //counter
    size_t points_index;
    size_t triangel_index;
    size_t actual_index; //counter
};


void endParenFunction(struct State* state, struct Data* data, char ch);
void openParenFunction(struct State* state, struct Data* data, char ch);
void nameFunction(struct State* state, struct Data* data, char ch);
void commaFunction(struct State* state, struct Data* data, char ch);
void numberFunction(struct State* state, struct Data* data, char ch);

void compile(struct State* state, struct Data* data, char ch);

#endif /* compilation_h */
