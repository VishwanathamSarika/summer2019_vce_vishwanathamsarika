#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h>

struct Stack
{
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

	if (!stack)
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (int*)malloc(stack->capacity * sizeof(int));

	if (!stack->array)
		return NULL;
	return stack;
}
int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}
char peek(struct Stack* stack)
{
	return stack->array[stack->top];
}
int pop(struct Stack* stack)
{
	if (!isEmpty(stack))
		return stack->array[stack->top--];
	return '$';
}
void push(struct Stack* stack, int op)
{
	stack->array[++stack->top] = op;
}

int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}
 
int evaluatePostfix(char* exp)
{
	struct Stack* stack = createStack(strlen(exp));
	int i,num;

	if (!stack) return -1;
 
	for (i = 0; exp[i]; ++i)
	{
		
		if (isdigit(exp[i])){
			num = 0;
			while (isdigit(exp[i])){
				num = num * 10 +exp[i]- '0';
				++i;
			}
			push(stack, num);
		}
 
		else
		{
			int val1 = pop(stack);
			int val2 = pop(stack);
			switch (exp[i])
			{
			case '+': push(stack, val2 + val1 ); break;
			case '-': push(stack, val2 - val1); break;
			case '*': push(stack, val2 * val1); break;
			case '/': push(stack, val2 / val1); break;
			}
		}
	}
	int res = pop(stack);
	return res;
}
 
int infixToPostfix(char* exp)
{
	char *postfixExp = (char *)malloc(50*sizeof(char));
	int i, k,num,num_length,j;

	struct Stack* stack = createStack(strlen(exp));
	if (!stack) 
		return -1;

	for (i = 0, k = -1; exp[i]; ++i)
	{ 
		if (isOperand(exp[i])){
			postfixExp[++k] = exp[i];
		}
		else if (isdigit(exp[i])){
			num = 0;
			num_length = 0;
			while (isdigit(exp[i])){
				num = num * 10 + exp[i] - '0';
				++i;
				num_length++;
			}
			i--;
			j = k;
			while (num > 0){
				postfixExp[k + num_length]=num % 10 + '0';
				num = num / 10;
				num_length--;
				j++;
			}
			k = j;
			postfixExp[++k] = ' ';
		}

		else if (exp[i] == '(')
			push(stack, exp[i]);

		else if (exp[i] == ')')
		{
			while (!isEmpty(stack) && peek(stack) != '('){
				postfixExp[++k] = pop(stack);
			}
			if (!isEmpty(stack) && peek(stack) != '(')
				return -1;              
			else
				pop(stack);
		}
		else 		{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack))){
				postfixExp[++k] = pop(stack);
			}
			push(stack, exp[i]);
		}

	}
	while (!isEmpty(stack)){
		postfixExp[++k] = pop(stack);
	}
	postfixExp[++k] = '\0';
	//printf("\nExpression is %s", exp);
	//printf("\nPostfix Expression is %s\n", postfixExp);
	//printf("\n%d", evaluatePostfix(postfixExp));
	return evaluatePostfix(postfixExp);
}

void test_ExpEval(){
	//char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
	//infixToPostfix(exp);
	char exp2[] = "12*10+(6*10)+2500";
	infixToPostfix(exp2);
}

