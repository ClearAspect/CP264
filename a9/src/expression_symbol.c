#include "expression_symbol.h"
#include "hash.h"

#include <stdlib.h>
#include <string.h>

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {

	QUEUE queue = {0, NULL, NULL}; // Initialize an empty queue
	STACK stack = {0, NULL};			 // Initialize an empty stack
	int i, type;
	char c;

	if (infixstr == NULL)
		return queue;

	for (i = 0; i < strlen(infixstr); i++) {
		c = infixstr[i];
		type = mytype(c);

		// Skip spaces
		if (type == 5)
			continue;

		// If it's an operand (digit), add it to the queue
		if (type == 0) {
			int num = 0;
			// Parse multi-digit number
			while (i < strlen(infixstr) && mytype(infixstr[i]) == 0) {
				num = num * 10 + (infixstr[i] - '0');
				i++;
			}
			i--; // Move back one position since the loop will increment i
			NODE *np = new_node(num, 0); // Create node for operand
			enqueue(&queue, np);
		} else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			char var_name[100] = {0};
			int j = 0;

			// Extract the variable name
			while (i < strlen(infixstr) &&
						 (((infixstr[i] >= 'a' && infixstr[i] <= 'z') ||
							 (infixstr[i] >= 'A' && infixstr[i] <= 'Z') ||
							 (infixstr[i] >= '0' && infixstr[i] <= '9') ||
							 infixstr[i] == '_'))) {
				var_name[j++] = infixstr[i++];
			}
			var_name[j] = '\0';
			i--; // Move back one position since the loop will increment i

			// Look up variable in hashtable
			HNODE *hn = hashtable_search(ht, var_name);
			int value = 0;

			// If variable exists, get its value
			if (hn != NULL) {
				value = hn->data.value;
			}

			// Create a node for the variable's value
			NODE *np = new_node(value, 0);
			enqueue(&queue, np);
		}
		// Left parenthesis - push to stack
		else if (type == 2) {
			NODE *np = new_node(c, type);
			push(&stack, np);
		}
		// Right parenthesis - pop from stack and add to queue until left
		// parenthesis
		else if (type == 3) {
			while (stack.top != NULL && stack.top->type != 2) {
				NODE *op = pop(&stack);
				op->next = NULL;
				enqueue(&queue, op);
			}

			// Discard the left parenthesis
			if (stack.top != NULL && stack.top->type == 2) {
				NODE *left_paren = pop(&stack);
				free(left_paren); // Don't need the parenthesis in the output
			}
		}
		// Operator
		else if (type == 1) {
			while (stack.top != NULL && stack.top->type == 1 &&
						 priority(stack.top->data) >= priority(c)) {
				NODE *op = pop(&stack);
				op->next = NULL;
				enqueue(&queue, op);
			}
			NODE *np = new_node(c, type);
			push(&stack, np);
		}
	}

	// Pop remaining operators from stack and add to queue
	while (stack.top != NULL) {
		NODE *op = pop(&stack);
		op->next = NULL;
		enqueue(&queue, op);
	}

	return queue;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
	if (infixstr == NULL || ht == NULL) {
		return 0;
	}

	// Convert infix expression to postfix
	QUEUE postfix_queue = infix_to_postfix_symbol(ht, infixstr);

	// Evaluate the postfix expression
	int result = evaluate_postfix(postfix_queue);

	// Clean up the queue
	clean_queue(&postfix_queue);

	return result;
}

int evaluate_postfix(QUEUE queue) {

	STACK stack = {0, NULL};
	NODE *current = queue.front;
	int result = 0;

	while (current != NULL) {
		// If it's an operand, push onto stack
		if (current->type == 0) {
			NODE *np = new_node(current->data, 0);
			push(&stack, np);
		}
		// If it's an operator, pop two operands and perform operation
		else if (current->type == 1) {
			if (stack.height < 2) {
				// Clean up and return 0 for invalid expression
				clean_stack(&stack);
				return 0;
			}

			// Pop the two operands
			NODE *op2_node = pop(&stack);
			op2_node->next = NULL;

			NODE *op1_node = pop(&stack);
			op1_node->next = NULL;

			int op1 = op1_node->data;
			int op2 = op2_node->data;
			int res = 0;

			// Perform the operation
			switch (current->data) {
			case '+':
				res = op1 + op2;
				break;
			case '-':
				res = op1 - op2;
				break;
			case '*':
				res = op1 * op2;
				break;
			case '/':
				if (op2 != 0)
					res = op1 / op2;
				else {
					// Division by zero, clean up and return 0
					free(op1_node);
					free(op2_node);
					clean_stack(&stack);
					return 0;
				}
				break;
			}

			// Free the operand nodes
			free(op1_node);
			free(op2_node);

			// Push the result back onto the stack
			NODE *res_node = new_node(res, 0);
			push(&stack, res_node);
		}

		current = current->next;
	}

	// The result should be the only item left on the stack
	if (stack.height == 1) {
		result = stack.top->data;
	}

	// Clean up the stack
	clean_stack(&stack);

	return result;
}

DATA evaluate_statement(HASHTABLE *ht, char *statement) {

	DATA data = {0};

	// Check if the statement is valid
	if (statement == NULL || ht == NULL) {
		return data;
	}

	// Parse the statement: variable = expression; or just variable
	char var_name[100] = {0};
	char expression[500] = {0};
	int i = 0, j = 0;
	int has_assignment = 0;

	// Skip leading whitespace
	while (statement[i] && (statement[i] == ' ' || statement[i] == '\t'))
		i++;

	// Extract variable name
	while (statement[i] && statement[i] != '=' && statement[i] != ' ' &&
				 statement[i] != '\t' && statement[i] != ';') {
		var_name[j++] = statement[i++];
	}
	var_name[j] = '\0';

	// Skip whitespace after variable name
	while (statement[i] && (statement[i] == ' ' || statement[i] == '\t'))
		i++;

	// Check if this is an assignment
	if (statement[i] == '=') {
		has_assignment = 1;
		i++; // Skip equals sign

		// Skip whitespace after equals sign
		while (statement[i] && (statement[i] == ' ' || statement[i] == '\t'))
			i++;

		// Extract expression until semicolon or end of string
		j = 0;
		while (statement[i] && statement[i] != ';') {
			expression[j++] = statement[i++];
		}
		expression[j] = '\0';

		// Evaluate the expression
		int value = evaluate_infix_symbol(ht, expression);

		// Create the DATA structure to return
		strcpy(data.name, var_name);
		data.value = value;

		// Insert or update the variable in the hash table
		hashtable_insert(ht, data);
	} else {
		// This is just a variable lookup
		HNODE *hn = hashtable_search(ht, var_name);
		if (hn != NULL) {
			// Variable exists, return its data
			data = hn->data;
		}
		// Otherwise, data remains with default values (name="", value=0)
	}

	return data;
}
