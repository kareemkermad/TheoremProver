#ifndef THEOREMPROVER_FORMULA_WRITER_H
#define THEOREMPROVER_FORMULA_WRITER_H

typedef struct tree_node tree_node;

int formula_length(tree_node* node);

void append(char** s, char c);

void infix(tree_node* node, char** formula);

#endif //THEOREMPROVER_FORMULA_WRITER_H
