/*
-------------------------------------------------------
Project: a1q3
File:    quadratic_ptest.c
Author:  HBF
Version: 2025-01-09
-------------------------------------------------------
*/
#include <stdio.h>
#include "quadratic.h"

float tests[][3] = {{0,1,2}, {1,2,1}, {1,-4,4},{1,2,2},{1,-1,-6}};

void test_solution_type(void) {
    printf("------------------\n");
    printf("Test: solution_type\n\n");
    int count = sizeof tests / sizeof *tests;
    for(int i = 0; i < count; i++) {
        printf("%s(%.1f %.1f %.1f): %d", "solution_type", tests[i][0], tests[i][1], tests[i][2], solution_type(tests[i][0], tests[i][1], tests[i][2]));
        printf("\n");
    }
    printf("\n");
}

void test_real_root_big(void) {
    printf("------------------\n");
    printf("Test: real_root_big\n\n");
    int count = sizeof tests / sizeof *tests;

    for(int i = 0; i < count; i++) {
        printf("%s(%.1f %.1f %.1f): %.1f", "real_root_big", tests[i][0], tests[i][1], tests[i][2], real_root_big(tests[i][0], tests[i][1], tests[i][2]));
        printf("\n");
    }    
    printf("\n");
}

void test_real_root_small(void) {
    printf("------------------\n");
    printf("Test: real_root_small\n\n");
    int count = sizeof tests / sizeof *tests;

    for(int i = 0; i < count; i++) {
        printf("%s(%.1f %.1f %.1f): %.1f", "real_root_small", tests[i][0], tests[i][1], tests[i][2], real_root_small(tests[i][0], tests[i][1], tests[i][2]));
        printf("\n");
    }    
    printf("\n");
}

int main(int argc, char *args[])
{
	if (argc <=1 ) { 
	test_solution_type();
	test_real_root_small();	
    test_real_root_big();
	}
	else {
		float a, b, c;
		int n = sscanf(args[1], "%f,%f,%f", &a, &b, &c); 
		if (n != 3) { 
			printf("command line argument like a,b,c, e.g. 1,2,3\n");	
		} else {
			printf("%s(%.1f %.1f %.1f): %d\n", "solution_type", a, b, c, solution_type(a, b, c));
			printf("%s(%.1f %.1f %.1f): %.1f\n", "real_root_small", a, b, c, real_root_small(a, b, c));
			printf("%s(%.1f %.1f %.1f): %.1f\n", "real_root_big", a, b, c, real_root_big(a, b, c));
		}
	}
	return 0;
}

