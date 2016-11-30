#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "tree.h"
#include "DNF_functions.h"
#define BUFF_LEN 4096
/*void print_tree(struct node*);
void fprint_tree(FILE* file, struct node*);*/
extern char tree_str[];
struct node* nalloc()
{
struct node* np;
/*XXX add: error checking for memory allocation np==-l*/
np = (struct node *) emalloc(sizeof(struct node));
if (np == NNULL)
	{mexPrintf("nalloc: Out of Memory\n");
	return ((struct node*)NULL);
	}
//printf(" Memory alloc done \n");
return np;
}

struct  node* add_leaf(char*  type,  char*  value)
{/*XXX  add:  error  checking  for  memory  allocation  np==-l*/
struct  node  *np  =  nalloc();
np->operator  =  type;
np->left.value  =  value;
//printf ("adding  leaf:  %s\twith leaf  value  :  %s\n", np->operator,  np->left.value);
return  np;
}

struct  node* add_node(char*  op,  struct  node  *left,  struct  node  *right)
{/*XXX  add:  error  checking  for  memory  allocation  np==-l*/
struct  node  *np  =  nalloc();
np->operator  =  op;
//printf("adding  node:  %s\n", np->operator);
np->left.np = left;
np->right.np = right;
return  np;
}

//check bcopy function
void apply_double_negation(struct  node*  snode)
{struct  node  *child,  *grandchild;
//printf("\napplydoublenegation");
child  =  LCHILD(snode);
grandchild  =  LCHILD(child);
memcpy(snode,grandchild,sizeof(struct  node));
mxFree(child);
mxFree(grandchild);
}

void apply_and_DeMorgan(struct  node*  snode)
{struct  node  *child,  *grandchildl,  *grandchild2,  *newchild;
child  =  LCHILD(snode);
grandchildl  =  LCHILD(child);
grandchild2  =  RCHILD(child);
snode->operator  =  "||";
child->operator = "!" ;
RCHILD(child)  =  NNULL;
newchild  =  add_node("!",  grandchild2,  NNULL);
RCHILD(snode)  =  newchild;
}

void apply_or_DeMorgan(struct  node*  snode)
{
/*XXX  e  applyandDeMorgan,  applyorDeMorgan  can  be  unified  to  one  functio~n  through
snode->operator  */
struct  node  *child,  *grandchildl,  *grandchild2,  *newchild;
child  =  LCHILD(snode);
grandchildl  =  LCHILD(child);
grandchild2  =  RCHILD(child);
snode->operator  =  "&&";
child->operator  =  "!" ;
RCHILD(child)  =  NNULL;
newchild  =  add_node("!",  grandchild2,  NNULL);
RCHILD(snode)  =  newchild;
}

//check bcopy function
void inverse_tokens(struct  node*  snode)
{struct  node  *child  =  NNULL;
int  relational  =  0;
child  =  LCHILD(snode);
if(strcmp(child->operator,"==") == 0)
	{child->operator  = "!=";
	relational  =  1;
	}
else if(strcmp(child->operator,  "!=")  ==0)
	{child->operator = "==" ;
	relational  =  1;
	}
else if(strcmp(child->operator,  "<")  ==  0)
	{child->operator  = ">=";
	relational  =  1;
	}
else if(strcmp(child->operator,  ">") == 0)
	{child->operator  =  "<=";
	relational  =  1;
	}
else if(strcmp(child->operator,  "<=")  ==  0)
	{child->operator  =  ">";
	relational  =  1;
	}
else if(strcmp(child->operator,  ">=")  ==  0)
	{child->operator  =  "<";
	relational  =  1;
	}
if(relational)
	{memcpy(snode,child,sizeof(struct  node));
	 mxFree(child);
	}
}

void permeate_nots(struct node* snode)
{	if (snode == NNULL)
	{return;
	}
//if root node operator is a NOT
	if (strcmp(snode->operator, "!") == 0)
	{
//printf("\npermeatenots: found a NOT");
		if (LCHILD(snode) != NNULL)
//if left child operator is a NOT
		{	if (strcmp(LCHILD(snode)->operator, "!") == 0)
			{//remove the two NOTs and permeate
			apply_double_negation(snode);
			permeate_nots(snode);
			}
			else if (strcmp(LCHILD(snode)->operator, "&&") == 0)
			{apply_and_DeMorgan(snode);
			}
			else if (strcmp(LCHILD(snode)->operator, "||") == 0)
			{apply_or_DeMorgan(snode);}
			else
			{//the node's operator is relational
			inverse_tokens(snode);
			}
		}
	}
/* if (strcmp(snode->operator, "VARIABLE") == 0)
printf("\npermeate nots: found a VARIABLE");
printf("\n\t snode->left.value %s", snode->left.value);
if (strcmp(snode->operator, "STRING") == 0)
printf("\npermeate nots: found a STRING");
printf("\n\t snode->left.value %s", snode->left.value);
}*/
	if ( (strcmp (snode ->operator, "VARIABLE") != 0) && (strcmp(snode->operator, "STRING") != 0))
	{permeate_nots (LCHILD (snode));
	 permeate_nots (RCHILD (snode));
	}
}

struct node* copy_bool_tree (struct node* snode)
{struct node *ctree;
	if (snode == NNULL)
	{return NNULL;
	}
//printf("\n%s",snode->operator);
//copy root node
/*XXX add: error checking for memory allocation ctree==-~l*/
ctree = nalloc();
//bcopy(snode, ctree, sizeof(struct node));
memcpy(ctree,snode, sizeof(struct node));
if ((strcmp(snode->operator, "VARIABLE") ==0) || (strcmp(snode->operator, "STRING") == 0)) 
	return ctree;

//copy left child
	if ( (strcmp(LCHILD(snode)->operator, "VARIABLE") !=0) || (strcmp(LCHILD(snode)->operator, "STRING") != 0))
	{	if (LCHILD(snode) != NNULL)
		{LCHILD(ctree) = copy_bool_tree(LCHILD(snode));
		}
	}
//copy right child
	if ( (strcmp(RCHILD(snode)->operator, "VARIABLE") !=0) || (strcmp(RCHILD(snode)->operator, "STRING") != 0))
	{	if (RCHILD(snode) != NNULL)
		{RCHILD(ctree) = copy_bool_tree(RCHILD(snode));
		}
	}
return ctree;
}

void distribute_branches (struct node* snode)
{	struct node *rchild, *cp_rchild, *gchildl, *gchild2;
	rchild = RCHILD(snode);
	/*mexPrintf("\n%s",rchild->operator);
	mexPrintf("\n%s",rchild->left.value);*/
	//if ((strcmp(rchild->operator, "VARIABLE") !=0) && (strcmp(rchild->operator, "STRING") != 0))
	cp_rchild =copy_bool_tree(rchild);
	//else
	//	cp_rchild = rchild;
	//print_tree(cp_rchild);
	gchildl = LCHILD(LCHILD(snode));
	gchild2 = RCHILD(LCHILD(snode));
	snode->operator = "||";
	LCHILD(snode)->operator = "&&";
	RCHILD(snode) = add_node("&&", gchild2, rchild);
	RCHILD(LCHILD(snode)) = cp_rchild;
	/*printf("\n");
	print_tree(LCHILD(snode));*/
	//print_tree(snode);
}


int and_distribute(struct node* snode)
{	int left, right;
	if (snode == NNULL)
	{return 0;
	}
	//if node is not an AND
	if (strcmp(snode->operator, "&&") != 0)
	{//if node is already an OR apply distributive law
	 //to its children
		if (strcmp(snode->operator, "||") == 0)
		{   //printf(" not AND cond\n");
			//print_tree(snode);
			//printf(" %s\n",LCHILD(snode)->operator);
			left = and_distribute(LCHILD(snode));
			right = and_distribute(RCHILD(snode));
			return (left || right);
		}
		else 
		{return 0;
		}
	}
	else
	{int swap = 0;
	struct node *temp;
	//if right child's operator is an-OR, swap positions of left and
	//right child (so if expression looked like x AND (y OR z)
	//it becomes (y OR z) AND x
	/*XXX missing check that LCHILD isn't already an OR */
		if (strcmp(RCHILD(snode)->operator, "||") == 0 && strcmp(LCHILD(snode)->operator, "||") != 0)
		{/*XXX add: error checking for memory allocation temp==-l */
		 temp = nalloc();
		 memcpy(temp,RCHILD(snode),sizeof(struct node));
		 memcpy(RCHILD(snode),LCHILD(snode), sizeof(struct node));
		 memcpy(LCHILD(snode),temp, sizeof(struct node));
		 swap = 1;
		 /*printf("\n");
		 print_tree(snode);*/
		 mxFree(temp);
		}
	//if left child is an OR, convert (y OR z) AND x to
	// (y AND x) OR (z AND x)
		if ( swap || (strcmp(LCHILD(snode)->operator, "||") == 0))
		{//mexPrintf("\n%s",LCHILD(snode)->operator);
		 distribute_branches(snode);
		 /*printf("\n");
		 print_tree(snode);*/
		 and_distribute(snode);
		 //print_tree(snode);
		 return 1;
		}
	//if left child is not an OR
		else
		{left = right = 0;
		 //if left child is not a leaf, apply distributive law to it
			if ((strcmp(LCHILD(snode)->operator, "VARIABLE") != 0) && (strcmp(LCHILD(snode)->operator, "STRING") != 0))
			{left = and_distribute(LCHILD(snode));
			 /*mexPrintf("\n");
			 print_tree(snode);*/
			}
			//if right child is not a leaf, apply distributive law to it
			if ( (strcmp(RCHILD(snode)->operator, "VARIABLE") != 0) && (strcmp(RCHILD(snode)->operator, "STRING") != 0))
			{right = and_distribute(RCHILD(snode));
			 /*printf("\n");
			 print_tree(snode);*/
			}
		 return (left || right);
		}
	}
}

void distribute_DNF(struct node* snode)
{int distribution = 1;
	while (distribution)
	{distribution = and_distribute(snode);
	}
}

void extract_DNF_tree(struct node* root)
{permeate_nots(root);
distribute_DNF(root);
}

int binary_node(struct node* snode)
{	if ((strcmp(snode->operator, "&&") == 0) || (strcmp(snode->operator, "||") == 0) ||
		(strcmp(snode->operator, "==") == 0) || (strcmp(snode->operator, "!=") == 0) ||
		(strcmp(snode->operator, "<") == 0) || (strcmp(snode->operator, ">") == 0) ||
		(strcmp(snode->operator, "<=") == 0) || (strcmp(snode->operator, ">=") == 0))
	{return 1;
	}
	else
	{return 0;
	}
}

char* print_binary_node(struct node* snode)
{
	char *binary_node_str = 0;
	char *temp_left = 0, *temp_right = 0;
	int node_str_length = 0;
	//print left child
	if (snode->left.np != NNULL)
	{
		temp_left = print_tree(snode->left.np);
	}
	//print operator
	node_str_length = strlen(temp_left) + strlen(snode->operator);
	//printf(" %s ", snode->operator);
	//print right child
	if (snode->right.np != NNULL)
	{
		temp_right = print_tree(snode->right.np);
	}
	node_str_length += strlen(temp_right);
	binary_node_str = (char*)malloc(node_str_length + 1);

	binary_node_str = strcpy(binary_node_str, "(");
	binary_node_str = strcat(binary_node_str, temp_left);
	binary_node_str = strcat(binary_node_str, snode->operator);
	binary_node_str = strcat(binary_node_str, temp_right);
	binary_node_str = strcat(binary_node_str, ")");


	//free(temp_left);
	//free(temp_right);

	return binary_node_str;
}

void print_binary_node2(struct node* snode)
{
	/*char *temp_left = 0, *temp_right = 0;
	int node_str_length = 0;*/
	//print left child
    strcat(tree_str,"(");
	if (snode->left.np != NNULL)
	{
		print_tree2(snode->left.np);
	}
	//print operator
	//node_str_length = strlen(temp_left) + strlen(snode->operator);
	//printf(" %s ", snode->operator);
	//print right child
    strcat(tree_str,snode->operator);
	if (snode->right.np != NNULL)
	{
		print_tree2(snode->right.np);
	}
    strcat(tree_str,")");
	/*node_str_length += strlen(temp_right);
	binary_node_str = (char*)emalloc(node_str_length + 1);

	binary_node_str = strcpy(binary_node_str, "(");
	binary_node_str = strcat(binary_node_str, temp_left);
	binary_node_str = strcat(binary_node_str, snode->operator);
	binary_node_str = strcat(binary_node_str, temp_right);
	binary_node_str = strcat(binary_node_str, ")");*/


	//free(temp_left);
	//free(temp_right);

	return;
}

char* print_unary_node(struct node* snode)
{
  char *unary_node_str=0,*temp_left=0;
 int node_str_length=0;
//print operator
//printf("%s", snode->operator);
//print left child
	if (snode->left.np != NNULL)
	{temp_left = print_tree(snode->left.np);
	}
node_str_length =strlen(temp_left)+ strlen(snode->operator);
unary_node_str = (char*) emalloc(node_str_length+1);

unary_node_str = strcpy(unary_node_str,"(");
unary_node_str = strcat(unary_node_str,snode->operator);
unary_node_str = strcat(unary_node_str,temp_left);
unary_node_str = strcat(unary_node_str,")");

//free(temp_left);
return unary_node_str;
}

void print_unary_node2(struct node* snode)
{
    /*char *unary_node_str=0,*temp_left=0;
    int node_str_length=0;*/
//print operator
//printf("%s", snode->operator);
//print left child
     strcat(tree_str,"(");
     strcat(tree_str,snode->operator);
	if (snode->left.np != NNULL)
	{
//        temp_left = print_tree(snode->left.np);
        print_tree2(snode->left.np);
	}
     strcat(tree_str,")");
/*node_str_length =strlen(temp_left)+ strlen(snode->operator);
unary_node_str = (char*) emalloc(node_str_length+1);

unary_node_str = strcpy(unary_node_str,"(");
unary_node_str = strcat(unary_node_str,snode->operator);
unary_node_str = strcat(unary_node_str,temp_left);
unary_node_str = strcat(unary_node_str,")");*/

//free(temp_left);
return ;
}

char* print_tree(struct node* snode)
{	
	char *node_str=0;
	int node_str_length;

	if (snode == NNULL)
		return NULL;

//if node is leaf print it
	if (strcmp(snode->operator, "STRING") == 0)
		{//printf(" %d ",strlen(snode->left.value));
		 node_str_length = strlen(snode->left.value);
		 node_str = (char*) emalloc(node_str_length+1);
		 node_str = strcpy(node_str,snode->left.value);
		//printf("\"%s\"",snode->left.value);
		}	
	else if (strcmp(snode->operator, "VARIABLE") == 0)
	{	//printf(" %d ",strlen(snode->left.value));
		node_str_length = strlen(snode->left.value);
		node_str = (char*) emalloc(node_str_length+1);
		node_str = strcpy(node_str,snode->left.value);
		//printf("%s",snode->left.value);
	}
//if node with two children
	else if (binary_node(snode))
	{//printf("(");
	node_str = print_binary_node(snode);
	//printf(")");
	}
//if node with one child
	else if (strcmp(snode->operator, "!") == 0)
	{//printf ("(");
	node_str = print_unary_node(snode);
	//printf(")");
	}
	return node_str;
}


void print_tree2(struct node* snode)
{	
	int node_str_length;

	if (snode == NNULL)
		return NULL;

//if node is leaf print it
	if (strcmp(snode->operator, "STRING") == 0)
		{//printf(" %d ",strlen(snode->left.value));
		 /*node_str_length = strlen(snode->left.value);
		 node_str = (char*) emalloc(node_str_length+1);
		 node_str = strcpy(node_str,snode->left.value);*/
         strcat(tree_str,snode->left.value);
        //printf("\"%s\"",snode->left.value);
		}	
	else if (strcmp(snode->operator, "VARIABLE") == 0)
	{	//printf(" %d ",strlen(snode->left.value));
		/*node_str_length = strlen(snode->left.value);
		node_str = (char*) emalloc(node_str_length+1);
		node_str = strcpy(node_str,snode->left.value);*/
        strcat(tree_str,snode->left.value);
		//printf("%s",snode->left.value);
	}
//if node with two children
	else if (binary_node(snode))
	{//printf("(");
	//node_str = print_binary_node(snode);
    print_binary_node2(snode);
	//printf(")");
	}
//if node with one child
	else if (strcmp(snode->operator, "!") == 0)
	{//printf ("(");
	//node_str = print_unary_node(snode);
    print_unary_node2(snode);
	//printf(")");
	}
	return;
}


/********modified above to return as string ******/
/*void print_binary_node(struct node* snode)
{	//print left child
	if (snode->left.np != NNULL)
	{print_tree(snode->left.np);
	}
	//print operator
	mexPrintf(" %s ", snode->operator);
	//print right child
	if (snode->right.np != NNULL)
	{print_tree(snode->right.np);
	}
}

void print_unary_node(struct node* snode)
{//print operator
mexPrintf("%s", snode->operator);
//print left child
	if (snode->left.np != NNULL)
	{print_tree(snode->left.np);
	}
}

void print_tree(struct node* snode)
{	if (snode == NNULL)
	return;
//if node is leaf print it
	if (strcmp(snode->operator, "STRING") == 0)
	{mexPrintf("\"%s\"",snode->left.value);
	}	
	else if (strcmp(snode->operator, "VARIABLE") == 0)
	{mexPrintf("%s",snode->left.value);
	}
//if node with two children
	else if (binary_node(snode))
	{mexPrintf("(");
	print_binary_node(snode);
	mexPrintf(")");
	}
//if node with one child
	else if (strcmp(snode->operator, "!") == 0)
	{mexPrintf ("(");
	print_unary_node(snode);
	mexPrintf(")");
	}
}*/

void fprint_binary_node(FILE* file, struct node* snode)
{//print left child
	if (snode->left.np != NNULL)
	{fprint_tree(file, snode->left.np);
	}
//print operator
	fprintf(file, " %s ", snode->operator);
//print right child
	if (snode->right.np != NNULL)
	{fprint_tree(file, snode->right.np);
	}
}

void fprint_unary_node(FILE* file, struct node* snode)
{//print operator
fprintf(file, "%s", snode->operator);
//print left child
	if (snode->left.np != NNULL)
	{fprint_tree(file, snode->left.np);
	}
}

void fprint_tree(FILE* file, struct node* snode)
{	if (snode == NNULL)
	{return;
	}
//if node is leaf print it
	if (strcmp(snode->operator, "STRING") == 0)
	{fprintf(file, "\"%s\"",snode->left.value);
	}
	else if (strcmp(snode->operator, "VARIABLE") == 0)
	{fprintf(file, "%s",snode->left.value);
	}
	//if node with two children
	else if (binary_node(snode))
	{fprintf(file, "(");
	 fprint_binary_node(file, snode);
	 fprintf(file, ")");
	}
//if node with one child
	else if (strcmp(snode->operator, "!") == 0)
	{fprintf(file, "(");
	 fprint_unary_node(file, snode);
	 fprintf(file, ")");
	}
}

void print_tree_file(struct node* snode)
{FILE *file;
	if ((file=fopen(targetdnf, "w")) != NULL)
	{fprint_tree(file, snode);
	fclose(file);
	}
	else
	/*XXX Incomplete error handling*/
	{mexPrintf("\nprinttreefile: error in opening file %i", errno);
	}
}


void free_tree(struct node* root)
{	if (root == NNULL)
	{return;
	}
//recursively free children
//if node has two children, free both of them
	if (binary_node(root))
	{free_tree(root->left.np);
	 free_tree(root->right.np);
	}
//if node has only one child, free this left child only
	else if(strcmp(root->operator, "!") == 0)
	{free_tree(root->left.np);
	}
/*freeing a leaf or the root*/
/*if ((strcmp(root->operator, "STRING") == 0) || (strcmp(root->operator, "VARIABLE")== 0))
mexPrintf("\nfreeing a leaf : %s", root->left.value);
else
mexPrintf("\nfreeing a root node: %s", root->operator);*/
mxFree(root);
return;
}
	