//
//  main.h
//  Pointy
//
//  Created by Niclas Schwalbe on 05.07.19.
//  Copyright © 2019 Niclas Schwalbe. All rights reserved.
//

#ifndef main_h
#define main_h

#define SPACE_FOR_POINTS 100
#define SPACE_FOR_RECTANGLES 100
/*For some reason, maximum size of any double represetend as a string:
 StackOverflow: What is the maximum length in chars needed to represent any double value?
 */
#define MAX_DIGITS_DOUBLE 3 + DBL_MANT_DIG - DBL_MIN_EXP
#define MAX_DIGITS_POINTS 5 + 3*MAX_DIGITS_DOUBLE

/*
 This is a rectangle to be stored:
 ((double,double,double),(double,double,double),(double,double,double))\0
 */
#define MAX_DIGITS_RECT 17+9*MAX_DIGITS_DOUBLE

void printPointList(char appened, char** points, size_t index);
void printRectangleList(char appened, char** rectangles, size_t index);
void setup(void);

#endif /* main_h */
