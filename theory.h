#ifndef THEOREMPROVER_THEORY_H
#define THEOREMPROVER_THEORY_H

#include <stdbool.h>

typedef struct tree_node tree_node;

/*
 * Theory node contains a formula and a pointer to the next node in the theory.
 */
typedef struct theory_node
{
    tree_node* formula;
    struct theory_node* next;
} theory_node;

/*
 * Theory is represented as a set of propositional formulas.
 */
typedef struct theory
{
    theory_node* front;
    theory_node* rear;
} theory;

bool is_literal(tree_node* formula);

bool is_not_literal(tree_node* formula);

theory_node* theory_node_create(tree_node* formula);

void theory_node_free(theory_node* node);

theory* theory_create();

void theory_free(theory* theory);

bool theory_contains(theory* theory, tree_node* formula);

bool theory_equals(theory* set1, theory* set2);

void theory_push(theory* theory, tree_node* formula);

tree_node* theory_pop(theory* theory);

tree_node* theory_pick_non_literal(theory* theory);

theory* theory_copy(theory* set);

bool theory_fully_expanded(theory* theory);

bool theory_contradictory(theory* theory);

#endif //THEOREMPROVER_THEORY_H