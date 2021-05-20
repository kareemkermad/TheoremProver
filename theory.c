#include "theory.h"
#include "tree.h"
#include "tokenizer.h"
#include <stdlib.h>

/*
 * A literal is defined as a proposition (p) or a negated proposition (-p).
 */
bool is_literal(tree_node* formula)
{
    if (formula != NULL)
    {
        token_type type = formula->token.type;
        if (type == proposition)
        {
            return true;
        }
        else if (type == negation)
        {
            tree_node* child = formula->left_child;
            type = child->token.type;
            if (type == proposition)
            {
                return true;
            }
        }
    }

    return false;
}

/*
 * A non-literal is defined as a (negated) formula with a binary connective.
 */
bool is_not_literal(tree_node* formula)
{
    return !is_literal(formula);
}

/*
 * Creates an isolated theory node initialized with a formula.
 */
theory_node* theory_node_create(tree_node* formula)
{
    theory_node* node = (theory_node*)malloc(sizeof(theory_node));
    node->formula = formula;
    node->next = NULL;
    return node;
}

/*
 * Frees the formula then the theory node.
 */
void theory_node_free(theory_node* node)
{
    tree_free(node->formula);
    free(node);
}

/*
 * Creates an empty theory.
 */
theory* theory_create()
{
    theory* set = (theory*)malloc(sizeof(theory));
    set->front = NULL;
    set->rear = NULL;
    return set;
}

/*
 * Frees the theory and all of the theory nodes.
 */
void theory_free(theory* theory)
{
    if (theory != NULL)
    {
        theory_node* node = theory->front;
        while (node != NULL)
        {
            theory_node* next = node->next;
            theory_node_free(node);
            node = next;
        }

        free(theory);
    }
}

/*
 * Checks if the theory contains a formula.
 */
bool theory_contains(theory* theory, tree_node* formula)
{
    for (theory_node* node = theory->front; node != NULL; node = node->next)
    {
        if (tree_equals(formula, node->formula))
        {
            return true;
        }
    }

    return false;
}

/*
 * Checks if two theories (sets of formulas) are equal.
 */
bool theory_equals(theory* set1, theory* set2)
{
    // Set equality is defined as: A = B ⟺ (A ⊆ B) and (B ⊆ A).
    theory_node* node;

    // A is a subset of B (A ⊆ B).
    for (node = set1->front; node != NULL; node = node->next)
    {
        // A is a subset of B iff every element of A is also an element of B.
        if (!theory_contains(set2, node->formula))
        {
            return false;
        }
    }

    // B is a subset of A (B ⊆ A).
    for (node = set2->front; node != NULL; node = node->next)
    {
        // B is a subset of A iff every element of B is also an element of A.
        if (!theory_contains(set1, node->formula))
        {
            return false;
        }
    }

    return true;
}

/*
 * Pushes formula to the end of the theory.
 */
void theory_push(theory* theory, tree_node* formula)
{
    if (formula != NULL)
    {
        theory_node* node = theory_node_create(formula);

        if (theory->rear != NULL)
        {
            theory->rear->next = node;
        }
        else
        {
            theory->front = node;
        }

        theory->rear = node;
    }
}

/*
 * Pops formula from the front of the theory.
 */
tree_node* theory_pop(theory* theory)
{
    theory_node* node = theory->front;

    if (node == NULL)
    {
        return NULL; // theory is empty.
    }

    theory->front = node->next;
    node->next = NULL;

    if (theory->front == NULL)
    {
        theory->rear = NULL;
    }

    tree_node* formula = node->formula;
    node->formula = NULL;
    theory_node_free(node);
    return formula;
}

/*
 * Pops the first non-literal formula form the theory and moves any literals to the back of the theory.
 */
tree_node* theory_pick_non_literal(theory* theory)
{
    tree_node* last = theory->rear->formula;
    if (last == NULL) { return NULL; } // theory is empty.
    tree_node* formula = NULL;

    do
    {
        formula = theory_pop(theory);

        if (is_not_literal(formula))
        {
            return formula;
        }

        theory_push(theory, formula);

    } while (formula != last);

    return NULL; // theory contains only literals.
}

/*
 * Creates a copy of the theory and all the formulas inside the theory.
 */
theory* theory_copy(theory* set)
{
    theory* theory_copy = theory_create();

    for (theory_node* node = set->front; node != NULL; node = node->next)
    {
        tree_node* formula_copy = tree_node_copy(node->formula);
        theory_push(theory_copy, formula_copy);
    }

    return theory_copy;
}

/*
 * Checks if theory is fully expanded (if each formula in the theory is a literal).
 */
bool theory_fully_expanded(theory* theory)
{
    for (theory_node* node = theory->front; node != NULL; node = node->next)
    {
        if (is_not_literal(node->formula))
        {
            return false;
        }
    }

    return true;
}

/*
 * Checks if theory is contradictory (if it contains a formula and its negation).
 */
bool theory_contradictory(theory* theory)
{
    for (theory_node* node1 = theory->front; node1 != NULL; node1 = node1->next)
    {
        for (theory_node* node2 = theory->front; node2 != NULL; node2 = node2->next)
        {
            tree_node* formula2 = node2->formula;
            char c = formula2->token.symbol;

            if (is_negation(c))
            {
                if (tree_equals(node1->formula, formula2->left_child))
                {
                    return true;
                }
            }
        }
    }

    return false;
}