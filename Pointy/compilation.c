//  Created by Niclas Schwalbe on 05.07.19.
//  Copyright © 2019 Niclas Schwalbe. All rights reserved.

#include "compilation.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <ctype.h> 

void compile(struct State* state, struct Data* data, char ch){
    switch(state->lastletter){
        case name:
            nameFunction(state, data, ch);
            break;
        case openparen:
            openParenFunction(state, data, ch);
            break;
        case number:
            numberFunction(state, data, ch);
            break;
        case endparen:
            endParenFunction(state, data, ch);
            break;
        case comma:
            commaFunction(state, data, ch);
            break;
        default:
            fprintf(stderr, "Error: Corrupted File.");
            return;
    }
}


void nameFunction(struct State* state, struct Data* data, char ch){
    if(ch == '('){
        state->lastletter = openparen;
        switch (state->shape) {
            case rectangle:
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                break;
            case point:
                data->points[data->points_index][data->actual_index++] = ch;
                break;
            default:
                break;
        }
    } else {
        state->lastletter = error;
    }
}

void openParenFunction(struct State* state, struct Data* data, char ch){
    if(ch == '('){
        switch (state->shape) {
            case rectangle:
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                state->lastletter = openparen;
                break;
            case point:
                state->lastletter = error;
                break;
            default:
                break;
        }
    }
    if(isdigit(ch)){
        data->numbers_written++;
        switch (state->shape) {
            case rectangle:
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                state->lastletter = number;
                break;
            case point:
                data->points[data->points_index][data->actual_index++] = ch;
                state->lastletter = number;
                break;
            default:
                break;
        }
    }
}


void endParenFunction(struct State* state, struct Data* data, char ch){
    switch (state->shape) {
        case point:
            data->points[data->points_index][data->actual_index++] = '\0';
            break;
        case rectangle:
            if(data->numbers_written > 9){
                data->triangle[data->triangel_index][data->actual_index++] = '\0';
                break;
            }
        default:
            break;
    }
    if(ch == '(' || ch == 'P'){
        if(++(data->points_index) >= SPACE_FOR_POINTS){
            printPointList(data->bool_appended_points, data->points, data->points_index-1);
            data->bool_appended_points = 1;
            //clear all Strings
            for(int i = 0; i < data->points_index; i++){
                data->points[i] = calloc(MAX_DIGITS_POINTS, 1);
            }
            data->points_index = 0;
        }
    }
    if(ch == '('){
        data->actual_index = 0;
        data->points[data->points_index][data->actual_index++] = ch;
        state->shape = point;
        state->lastletter = openparen;
        data->numbers_written = 0;
        return;
    }
    if(ch == 'P'){
        data->actual_index = 0;
        state->lastletter = name;
        state->shape = point;
        data->numbers_written = 0;
        return;
    }
    if(ch == 'R'){
        if(++(data->triangel_index) >= SPACE_FOR_RECTANGLES){
            printRectangleList(data->bool_appended_triangel, data->triangle, (data->triangel_index)-1);
            data->bool_appended_triangel = 1;
            //clear all strings
            for(int i = 0; i < data->triangel_index; i++){
                data->triangle[i] = calloc(MAX_DIGITS_RECT, 1);
            }
            data->triangel_index = 0;
        }
        data->actual_index = 0;
        state->lastletter = name;
        state->shape = rectangle;
        data->numbers_written = 0;
        return;
    }
    if(ch == ','){
        if(state->shape == rectangle){
            if(data->numbers_written < 9){
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                state->lastletter = comma;
            } else {
                state->lastletter = error;
            }
        }
        return;
    }
    if(ch == ')'){
        if(state->shape == rectangle){
            data->triangle[data->triangel_index][data->actual_index++] = ch;
            data->triangle[data->triangel_index][data->actual_index++] = '\0';
            return;
        }
    }
    state->lastletter = error;
}

void commaFunction(struct State* state, struct Data* data, char ch){
    switch (state->shape) {
        case point:
            if(isdigit(ch)){
                data->numbers_written++;
                state->lastletter = number;
                data->points[data->points_index][data->actual_index++] = ch;
                break;
            }
            state->lastletter = error;
            break;
        case rectangle:
            if(isdigit(ch)){
                data->numbers_written++;
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                state->lastletter = number;
                break;
            }
            if(ch == '('){
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                state->lastletter = openparen;
                break;
            }
            state->lastletter = error;
            break;
        default:
            break;
    }
}
void numberFunction(struct State* state, struct Data* data, char ch){
    if(isdigit(ch)){
        switch (state->shape) {
            case rectangle:
                data->triangle[data->triangel_index][data->actual_index++] = ch;
                break;
            case point:
                data->points[data->points_index][data->actual_index++] = ch;
                break;
            default:
                break;
        }
        return;
    }
    if(ch == ','){
        switch (state->shape) {
            case rectangle:
                if(data->numbers_written <= 9){
                    data->triangle[data->triangel_index][data->actual_index++] = ch;
                    state->lastletter = comma;
                } else {
                    state->lastletter = error;
                }
                break;
            case point:
                if(data->numbers_written <= 3){
                    data->points[data->points_index][data->actual_index++] = ch;
                    state->lastletter = comma;
                } else {
                    state->lastletter = error;
                }
            default:
                break;
        }
        return;
    }
    if(ch == ')'){
        switch (state->shape) {
            case rectangle:
                if(data->numbers_written%3 == 0){
                    data->triangle[data->triangel_index][data->actual_index++] = ch;
                    state->lastletter = endparen;
                } else {
                    state->lastletter = error;
                }
                break;
            case point:
                //printf("%d", numbers_written);
                if(data->numbers_written == 3){
                    state->lastletter = endparen;
                    data->points[data->points_index][data->actual_index++] = ch;
                } else {
                    state->lastletter = error;
                }
                break;
            default:
                break;
        }
        return;
    }
    if(ch == '.'){
        data->points[data->points_index][data->actual_index++] = ch;
        return;
    }
    state->lastletter = error;
}

