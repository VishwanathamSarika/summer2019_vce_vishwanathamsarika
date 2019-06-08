#ifndef StackUtils_h
#define StackUtils_h

struct Stack
{
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(unsigned capacity);
int isEmpty(struct Stack* stack);
char peek(struct Stack* stack);
int pop(struct Stack* stack);
void push(struct Stack* stack, int op);

#endif