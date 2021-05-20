#ifndef THEOREMPROVER_TREE_H
#define THEOREMPROVER_TREE_H

#include <stdbool.h>
#include "token.h"

/*
 * Alpha formulas are those that simplify (in one step) to a conjunction of two subformulas or are double negations.
 * Beta formulas are those which simplify (in one step) to a disjunction of two subformulas.
 */
typedef enum formula_type
{
    alpha,
    beta
} formula_type;

/*
 * Binary tree node contains a token and a pointer to the root nodes of the left and right subtrees.
 */
typedef struct tree_node
{
    token token;
    struct tree_node* left_child;
    struct tree_node* right_child;
} tree_node;

tree_node* tree_node_create(token token);

void tree_free(tree_node* node);

bool tree_equals(tree_node* node1, tree_node* node2);

tree_node* tree_node_copy(tree_node* node);

tree_node* negated_formula(token negation, tree_node* formula);

tree_node* proposition_formula(token proposition);

tree_node* binary_formula(token binary, tree_node* left_formula, tree_node* right_formula);

formula_type get_formula_type(tree_node* formula, tree_node** exp1, tree_node** exp2);

#endif //THEOREMPROVER_TREE_H
