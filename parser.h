#ifndef THEOREMPROVER_PARSER_H
#define THEOREMPROVER_PARSER_H

#include "tree.h"

tree_node* parse_binary_formula(char* formula, int* offset, token* current_token);

tree_node* parse_negated_formula(char* formula, int* offset, token* current_token);

tree_node* parse_formula(char* formula, int* offset, token* current_token);

tree_node* parse(char* formula);

#endif //THEOREMPROVER_PARSER_H
