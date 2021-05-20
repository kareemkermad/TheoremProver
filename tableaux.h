#ifndef THEOREMPROVER_TABLEAUX_H
#define THEOREMPROVER_TABLEAUX_H

#include "theory.h"

/*
 * Tableau node contains a theory and a pointer to the next node in the tableau.
 */
typedef struct tableau_node
{
    theory* theory;
    struct tableau_node* next;
} tableau_node;

/*
 * Tableau is represented as a queue of theories.
 */
typedef struct tableau
{
    tableau_node* front;
    tableau_node* rear;
} tableau;

tableau_node* tableau_node_create(theory* theory);

void tableau_node_free(tableau_node* node);

tableau* tableau_create();

void tableau_free(tableau* tableau);

bool tableau_contains(tableau* tableau, theory* theory);

void tableau_enqueue(tableau* tableau, theory* theory);

theory* tableau_dequeue(tableau* tableau);

bool tableau_empty(tableau* tableau);

void tableau_init(tableau* tableau, tree_node* formula);

bool tableau_algorithm(tree_node* formula);

bool is_satisfiable(tree_node* formula);

bool is_valid(tree_node* formula);

#endif //THEOREMPROVER_TABLEAUX_H
