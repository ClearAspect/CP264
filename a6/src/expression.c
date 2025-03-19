
#include "expression.h"
#include "common.h"
#include "stack.h"
#include <stdlib.h>
#include <string.h>

QUEUE infix_to_postfix(char *infixstr) {
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

		// If it's an operand, add it to the queue
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
				NODE *op = stack.top;
				stack.top = stack.top->next;
				stack.length--;
				op->next = NULL;
				enqueue(&queue, op);
			}

			// Discard the left parenthesis
			if (stack.top != NULL && stack.top->type == 2) {
				NODE *left_paren = stack.top;
				stack.top = stack.top->next;
				stack.length--;
				free(left_paren); // Don't need the parenthesis in the output
			}
		}
		// Operator
		else if (type == 1) {
			while (stack.top != NULL && stack.top->type == 1 &&
						 priority(stack.top->data) >= priority(c)) {
				NODE *op = stack.top;
				stack.top = stack.top->next;
				stack.length--;
				op->next = NULL;
				enqueue(&queue, op);
			}
			NODE *np = new_node(c, type);
			push(&stack, np);
		}
	}

	// Pop remaining operators from stack and add to queue
	while (stack.top != NULL) {
		NODE *op = stack.top;
		stack.top = stack.top->next;
		stack.length--;
		op->next = NULL;
		enqueue(&queue, op);
	}

	return queue;
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
			// Check if there are enough operands
			if (stack.length < 2) {
				// Clean up and return 0 for invalid expression
				clean_stack(&stack);
				return 0;
			}

			// Pop the two operands
			NODE *op2_node = stack.top;
			stack.top = stack.top->next;
			stack.length--;
			op2_node->next = NULL;

			NODE *op1_node = stack.top;
			stack.top = stack.top->next;
			stack.length--;
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
	if (stack.length == 1) {
		result = stack.top->data;
	}

	// Clean up the stack
	clean_stack(&stack);

	return result;
}

int evaluate_infix(char *infixstr) {
	// Convert infix to postfix
	QUEUE postfix = infix_to_postfix(infixstr);

	// Evaluate the postfix expression
	int result = evaluate_postfix(postfix);

	// Clean the postfix queue
	clean_queue(&postfix);

	return result;
}
