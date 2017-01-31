#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mex.h"
#include "tree.h"
//#include "DNF_functions.h"
extern struct node* add_leaf(char* ,char*);
extern struct node* add_node(char*,  struct  node*,struct  node*);

# define NUMBER_STRINGS 10
# define STRING_MAX_SIZE 10
char * emalloc(size_t n)
{       
	char *tmp;
	
	if (!(tmp = (char *) mxMalloc(n)))
        mexErrMsgTxt("mx_debugging: not enough memory!");
	memset(tmp, 0, n);
	return tmp;
}
char** extract_tokens(char * bool_string)
{	
	int i,string_length,num_of_spaces,num_of_tokens;
	char **bool_tokens=0;
	string_length = strlen(bool_string);
	num_of_spaces = 0;
	for (i=0;i<string_length;i++)
		{if (bool_string[i] == ' ')
			num_of_spaces+=1;
		}
	bool_tokens = (char*)mxMalloc((string_length -num_of_spaces) * sizeof(char*));
	memset(bool_tokens,0,(string_length -num_of_spaces) * sizeof(char*));
	num_of_tokens = 0;
	bool_tokens[0] = strtok(bool_string," ");
	if (bool_tokens[0] != NULL)
		{i = 1;
		while ((bool_tokens[i] = strtok(NULL, " ")) != NULL)
			i++;
		num_of_tokens = i;
		}
	/*for (i=0;bool_tokens[i];i++)
		mexPrintf("%s",bool_tokens[i]);*/

	return bool_tokens;
}
struct Stack
{
	int top;
	unsigned capacity;
	char** array;
};

// Stack Operations
struct Stack* createStack( unsigned capacity )
{
	struct Stack* stack = (struct Stack*) mxMalloc(sizeof(struct Stack));

	if (!stack) 
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (char*) mxMalloc(stack->capacity * sizeof(char*));

	if (!stack->array)
		{mxFree(stack);
		return NULL;
		}
	return stack;
}
int isEmpty(struct Stack* stack)
{
	return stack->top == -1 ;
}
char* peek(struct Stack* stack)
{
	return stack->array[stack->top];
}
char* pop(struct Stack* stack)
{
	if (!isEmpty(stack))
		return stack->array[stack->top--] ;
	return ((char*)0);
}
void push(struct Stack* stack, char* op)
{
	//mexPrintf(" \n %s \n ",op );
	stack->array[++stack->top] = op;
}


// A utility function to check if the given character is operand
int isOperand(char* ch)
{
	char temp;
	temp = ch[0];
	if ((strcmp(ch,"&&")==0)||(strcmp(ch,"||")==0)||(strcmp(ch,"!")==0)||(strcmp(ch,"(")==0)||(strcmp(ch,")")==0))
		return 0;
	else 
		{if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z'))
			return 1;
		else 
			return 0;
		}
}

int isOperator(char* ch)
{
	if ((strcmp(ch,"&&")==0)||(strcmp(ch,"||")==0)||(strcmp(ch,"!")==0))
		return 1;
	else 
		return 0;
}
int isbinaryOperator(char* ch)
{
	if ((strcmp(ch,"&&")==0)||(strcmp(ch,"||")==0))
		return 1;
	else 
		return 0;
}



// The main function that converts given infix expression
// to postfix expression. 
int infixToPostfix(char **exp,int num_of_tokens )
//int infixToPostfix(char exp[][STRING_MAX_SIZE])
{
	int i, k;
	struct Stack* stack;

	// Create a stack of capacity equal to expression size 
	stack = createStack(num_of_tokens);
	if(!stack) // See if stack was created successfully 
		return -1 ;
	for (i = 0, k = -1; i < num_of_tokens; ++i)
	{
		// If the scanned character is an operand, add it to output.
		if (isOperand(exp[i]))
			{/*if (i==9)
			{mexPrintf("%s",exp[i]);
			}*/
			exp[++k] = exp[i];
			}
		// If the scanned character is an ‘(‘, push it to the stack.
		else if (strcmp(exp[i],"(")==0)
			push(stack, exp[i]);	
		// If the scanned character is an ‘)’, pop and output from the stack 
		// until an ‘(‘ is encountered.
		else if (strcmp(exp[i],")")==0)
		{
			while (!isEmpty(stack) && strcmp(peek(stack),"("))
				exp[++k] = pop(stack);
			if (!isEmpty(stack) && strcmp(peek(stack),"("))
				return -1; // invalid expression			 
			else
				pop(stack);
		}
		else // an operator is encountered
		{	//mexPrintf( "operator case: %s\n", peek(stack) );
			while (!isEmpty(stack) && strcmp(peek(stack),"(")!=0) // && Prec(exp[i]) <= Prec(peek(stack)))
				exp[++k] = pop(stack);
			push(stack, exp[i]);
		}
	}
	// pop all the operators from the stack
	while (!isEmpty(stack))
		exp[++k] = pop(stack );

	exp[++k] = 0;
	
	mxFree(stack->array);
	mxFree(stack);
	return 0;
}

struct node* create_tree(char** token_array)
{	int i,num_of_tokens=0;
	struct Stack* stack;
	struct node* tree_root,*right_child,*left_child,*parent,*temp;
	//char *right_ch,*left_ch;
	//tree_root= (struct node*)mxMalloc(sizeof(struct node));
	for (i=0;token_array[i];i++)
		num_of_tokens += 1;

	// Create a stack of capacity equal to expression size 
	stack = createStack(num_of_tokens);
	if(!stack) // See if stack was created successfully 
		return ((struct node*)NULL) ;
	for (i = 0; i < num_of_tokens; ++i)
		{if (isOperand(token_array[i]))
			{temp = add_leaf("VARIABLE",token_array[i]);
			push(stack, (char*)temp);
			}
		else if (isOperator(token_array[i]))
			{if (isbinaryOperator(token_array[i]))
				{
				right_child = (struct node *)pop (stack);
				left_child = (struct node *)pop (stack);
				//mexPrintf("%s",left_child->left.value);
				//mexPrintf("%s",right_child->left.value);
				parent = add_node(token_array[i],left_child,right_child);
				}
			else
				{
				 left_child = (struct node *)pop (stack);
				 parent = add_node(token_array[i],left_child,NULL);
				}
			//temp = parent;
			push(stack,(char*)parent);
			}
		}
	tree_root = (struct node*)pop(stack);
	mxFree(stack->array);
	mxFree(stack);
	return tree_root;
}

// Driver program to test above functions
/*int main()
{	
	char** bool_tokens = 0;
	char bool_str[] = "( ( p1 && p2 ) || ( p3 && p4 ) )";
	int i,num_of_tokens=0;
	mexPrintf("\n orginal: %s\n",bool_str);
	bool_tokens = extract_tokens(bool_str);

	for (i=0;bool_tokens[i];i++)
		num_of_tokens += 1;
	infixToPostfix(bool_tokens,num_of_tokens);
	mexPrintf("\n");
	for (i=0;bool_tokens[i];i++)
		mexPrintf("%s",bool_tokens[i]);

}*/

	