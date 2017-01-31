struct Stack
{
	int top;
	unsigned capacity;
	char** array;
};

char** extract_tokens(char *bool_string);
struct Stack* createStack( unsigned int capacity );
int isEmpty(struct Stack* stack);
char* peek(struct Stack* stack );
char* pop(struct Stack* stack);
void push(struct Stack* stack ,char* op);
int isOperand(char* ch);
int isOperator(char* ch );
int isbinaryOperator(char* ch);
int infixToPostfix(char ** exp,int num_of_tokens);
struct node* create_tree(char**);