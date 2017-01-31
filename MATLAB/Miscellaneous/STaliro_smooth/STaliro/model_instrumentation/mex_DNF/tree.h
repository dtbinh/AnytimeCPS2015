/* node
"* There can be two types of nodes: intermediate and leaf/terminal nodes
* An intermediate node uses:
* operator, which can be: a logical or relational operator
* left, which contains:
* np pointer to left child node
* and may also use (if the operator is binary)
* right, which contains:
* np pointer to right child node
"* (Fields not mentioned are empty/ignored)
"* A leaf node has:
* operator, which can be: a VARIABLE or STRING indicator
* left, which contains:
* value actual value of VARIABLE or STRING
* (Fields not mentioned are empty/ignored)*/
#ifndef _tree_h
	#define _tree_h
	struct node
	{char* operator;
	union
		{char* value;
		struct node *np;
		} left, right;
	};

	char* targetdnf;
char	*emalloc(size_t);	
	#define LCHILD(snode) ((snode)->left.np)
	#define RCHILD(snode) ((snode)->right.np)
	#define NNULL ((struct node *) 0)
#endif