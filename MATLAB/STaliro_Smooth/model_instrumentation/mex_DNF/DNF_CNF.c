
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "tree.h"
#include "str2tree.h"
#include "DNF_functions.h"
#define BUFF_LEN 4096

char tree_str[BUFF_LEN];

void emptystr(){
    int i;
    for(i=0; i<BUFF_LEN ; i++){
        tree_str[i]='\0';
    }
}

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
	struct node* n4;
	char** bool_tokens = 0;
	char bool_str[4096];// = "( ( p1 || p2 ) && ( p3 || p4 ) )";
	int i,num_of_tokens=0;
    int rows,cols,status;  
    int dims[] = {1, 100};
    char *tree_string;
	//plhs[0]= mxCreateCharArray(2, (const int *)dims);
    //plhs[0]="hi";
    
    if (nrhs == 0)
        mexErrMsgTxt("DNF_CNF: Input argument empty.");
    if(nlhs > 1)
		mexErrMsgTxt("Too many output arguments.");
    
	//plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    //plhs[0] = mxCreateString(const char *str);
    //plhs[0] = mxCreateCharArray(1, const int *dims);
    rows = mxGetM(prhs[0]);
    cols = mxGetN(prhs[0]);
    
    if ( rows > 1 )
        mexErrMsgTxt("the formuala should be a sinle row \n");

    status = mxGetString(prhs[0],bool_str,cols+1);
    if (status == 1)
        {mexErrMsgTxt("\n Could not copy the input string.String too large.\n");
        }
     
    mexPrintf("\n orginal string: %s\n",bool_str);

	bool_tokens = extract_tokens(bool_str);
	for (i=0;bool_tokens[i];i++)
		num_of_tokens += 1;

	infixToPostfix(bool_tokens,num_of_tokens);
	/***** printing the postfix expression****/

	printf("\n postfix expression: ");
	for (i=0;bool_tokens[i];i++)
		mexPrintf("%s",bool_tokens[i]);
	n4 = create_tree(bool_tokens);
	/******done printing ********/

	mexPrintf("\n");
    emptystr();
    strcpy(tree_str,"");
//	tree_string = print_tree(n4);
	print_tree2(n4);
	mexPrintf("b4 dnf: %s", tree_str);
//	mexPrintf("b4 dnf: %s", tree_string);
	extract_DNF_tree(n4);
	mexPrintf("\n");
	emptystr();
	strcpy(tree_str, "");
	print_tree2(n4);
//	tree_string = print_tree(n4);
    //print_tree2(n4, tree_str);
    mexPrintf("after dnf %s",tree_str);
//    mexPrintf("b4 dnf: %s", tree_string);
	plhs[0] = mxCreateString(tree_str);
//	plhs[0] = mxCreateString(bool_str);
 	free_tree(n4);
	emptystr();
// 	mxFree(tree_str);
//	mexPrintf("\n tree printed \n");
}