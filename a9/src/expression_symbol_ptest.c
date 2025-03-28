/*
 -------------------------------------------------------
 File:     expression_symbol_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2025-03-13
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "expression_symbol.h"   
#include "hash.h"

char infilename[40] = "expression.txt";

void display_hashtable(HASHTABLE *ht);

int htsize = 10;

DATA keyvalue_tests[] = { { "a", 10 }, { "b", 8 }, { "c", 2 }, { "d", 3 } };

char expression_tests[][80] = { "a+b", "a+b+c+d", "a+b*c", "(a-b)*(c+d)" };

char statement_tests[][80] = { "a=10", "b=8", "d=2", "c=(a+b)*(a-b)", "b=d*c",
		"e=12", "f=e/d", "b", "k" };

HASHTABLE *ht = NULL;

void test_before() {
	ht = new_hashtable(htsize);
	int n = sizeof keyvalue_tests / sizeof *keyvalue_tests;
	for (int i = 0; i < n; i++) {
		hashtable_insert(ht, keyvalue_tests[i]);
	}
	printf("keyalue_tests_hashtable: ");
	display_hashtable(ht);
	printf("\n");
}

void test_end() {
	hashtable_clean(&ht);
}

void test_infix_to_postfix_symbol() {
	printf("------------------\n");
	printf("Test: infix_to_postfix\n\n");
	int n = sizeof expression_tests / sizeof *expression_tests;
	QUEUE q = { 0 };
	for (int i = 0; i < n; i++) {
		q = infix_to_postfix_symbol(ht, expression_tests[i]);
		printf("infix_to_postfix_symbol(%s): ", expression_tests[i]);
		display(q.front);
		clean_queue(&q);
		printf("\n");
	}
	printf("\n");
}

void test_evaluate_infix_symbol() {
	printf("------------------\n");
	printf("Test: evaluate_infix_symbol\n\n");
	int n = sizeof expression_tests / sizeof *expression_tests;
	for (int i = 0; i < n; i++) {
		printf("evaluate_infix_symbol(%s): %d", expression_tests[i],
				evaluate_infix_symbol(ht, expression_tests[i]));
		printf("\n");
	}
	printf("\n");
}

void test_evaluate_statement() {
	printf("------------------\n");
	printf("Test: evaluate_statement\n\n");
	int n = sizeof statement_tests / sizeof *statement_tests;
	for (int i = 0; i < n; i++) {
		DATA hd = evaluate_statement(ht, statement_tests[i]);
		if (*hd.name)
			printf("evaluate_statement(%s): %s %d",
					statement_tests[i], hd.name, hd.value);
		else
			printf("evaluate_statement(%s): null\n",
					statement_tests[i]);
		printf("\n");
	}
	printf("\n");
}

void test_evaluate_statements_file() {
	printf("------------------\n");
	printf("Test: evaluate_statements_file(\n\n");

	char line[100];
	char delimiters[] = ";\n";
	char *st;

	FILE *fp = fopen(infilename, "r");
	if (fp==NULL) printf("File not exists\n");

	printf("Symbolic expressions:\n");
	while (fgets(line, sizeof(line), fp) != NULL) {
		st = strtok(line, delimiters);
		if (st)
			printf("%s\n", st);
		while (st != NULL) {
			evaluate_statement(ht, st);
			st = strtok(NULL, delimiters);
		}
	}
	fclose(fp);

	printf("\nSymbolic expression evaluation:\n");
	display_hashtable(ht);
	hashtable_clean(&ht);
	printf("\n");
}

void interative_statement(char *expstr) {
	char line[100];
	sscanf(expstr, "%s", line);
	do {
		//printf("statement: %s\n", line);
		if (strcmp(line, "all") == 0) {
			display_hashtable(ht);
			printf("\n");
		} else {
			if (strstr(line, "=")) {
				DATA hd = evaluate_statement(ht, line);
				if (*hd.name)
					printf("%s=%d\n", hd.name, hd.value);
				else
					printf("invalid statement\n");
		    }
			else {
				int value = evaluate_infix_symbol(ht, line);
				printf("%d\n", value);
			}
		}
		printf("enter a statement: e.g. a=(2+3)*2, or all to display hashtable, or quit to exit\n");
		gets(line);
		if (strcmp(line, "quit") == 0)
			break;
		
	} while (1);
}

int main(int argc, char *args[]) {
	if (argc <= 1) {
		test_before();
		test_infix_to_postfix_symbol();
		test_evaluate_infix_symbol();
		test_evaluate_statement();
		test_end();
	} else {
		ht = new_hashtable(htsize);
		int option = 0;
		if (sscanf(args[1], "%d", &option) >= 1) {
			switch (option) {
			case 0:
			    if (argc > 2)
				strcpy(infilename, args[2]);
				test_evaluate_statements_file();
				break;
			case 1:
				interative_statement("a=(2+3)");
				break;
			}
		}
		hashtable_clean(&ht);
	}
	return 0;
}

void display_hashtable(HASHTABLE *ht) {
	int i = 0;
	HNODE *p = NULL;
	for (i = 0; i < ht->size; i++) {
		p = *(ht->hna + i);
		if (p) {
			while (p) {
				printf("(%s %d) ", p->data.name, p->data.value);
				p = p->next;
			}
		}
	}
}

