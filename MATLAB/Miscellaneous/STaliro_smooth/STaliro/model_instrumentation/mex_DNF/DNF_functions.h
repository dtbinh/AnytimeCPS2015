#include <stdio.h>
#include <errno.h>
struct node* nalloc();
struct  node* add_leaf(char*  type,  char*  value);
struct  node* add_node(char*  op,  struct  node  *left,  struct  node  *right);
void apply_double_negation(struct  node*  snode);
void apply_and_DeMorgan(struct  node*  snode);
void apply_or_DeMorgan(struct  node*  snode);
void inverse_tokens(struct  node*  snode);
void permeate_nots(struct node* snode);
struct node* copy_bool_tree (struct node* snode);
void distribute_branches (struct node* snode);
int and_distribute(struct node* snode);
void distribute_DNF(struct node* snode);
void extract_DNF_tree(struct node* root);
int binary_node(struct node* snode);
/*void print_binary_node(struct node* snode);
void print_unary_node(struct node* snode);
void print_tree(struct node* snode);*/
char* print_binary_node(struct node* snode);
char* print_unary_node(struct node* snode);
char* print_tree(struct node* snode);
void print_tree2(struct node* snode);
void print_binary_node2(struct node* snode);
void print_unary_node2(struct node* snode);
void fprint_binary_node(FILE * file, struct node* snode);
void fprint_unary_node(FILE* file, struct node* snode);
void fprint_tree(FILE* file, struct node* snode);
void print_tree_file(struct node* snode);
void free_tree(struct node* root);
