#include "tableaux.h"
#include "tree.h"
#include <stdlib.h>

/*
 * Creates an isolated tableau node initialized with a theory.
 */
tableau_node* tableau_node_create(theory* theory)
{
    tableau_node* node = (tableau_node*)malloc(sizeof(tableau_node));
    node->theory = theory;
    node->next = NULL;
    return node;
}

/*
 * Frees the theory then the tableau node.
 */
void tableau_node_free(tableau_node* node)
{
    theory_free(node->theory);
    free(node);
}

/*
 * Creates an empty tableau.
 */
tableau* tableau_create()
{
    tableau* tab = (tableau*)malloc(sizeof(tableau));
    tab->front = NULL;
    tab->rear = NULL;
    return tab;
}

/*
 * Frees the tableau and all of the tableau nodes.
 */
void tableau_free(tableau* tableau)
{
    if (tableau != NULL)
    {
        tableau_node* node = tableau->front;
        while (node != NULL)
        {
            tableau_node* next = node->next;
            tableau_node_free(node);
            node = next;
        }

        free(tableau);
    }
}

/*
 * Checks if the tableau contains a theory.
 */
bool tableau_contains(tableau* tableau, theory* theory)
{
    for (tableau_node* node = tableau->front; node != NULL; node = node->next)
    {
        if (theory_equals(theory, node->theory))
        {
            return true;
        }
    }

    return false;
}

/*
 * Pushes theory to the end of the the tableau queue.
 */
void tableau_enqueue(tableau* tableau, theory* theory)
{
    tableau_node* node = tableau_node_create(theory);

    if (tableau->rear != NULL)
    {
        tableau->rear->next = node;
    }
    else
    {
        tableau->front = node;
    }

    tableau->rear = node;
}

/*
 * Pops theory from the front of the tableau queue.
 */
theory* tableau_dequeue(tableau* tableau)
{
    tableau_node* node = tableau->front;

    if (node == NULL)
    {
        return NULL; // tableau is empty.
    }

    tableau->front = node->next;
    node->next = NULL;

    if (tableau->front == NULL)
    {
        tableau->rear = NULL;
    }

    theory* theory = node->theory;
    node->theory = NULL;
    tableau_node_free(node);
    return theory;
}

/*
 * Checks if the tableau is empty.
 */
bool tableau_empty(tableau* tableau)
{
    return tableau->front == NULL;
}

/*
 * Initializes the tableau with root theory.
 */
void tableau_init(tableau* tableau, tree_node* formula)
{
    theory* theory = theory_create();
    theory_push(theory, formula);
    tableau_enqueue(tableau, theory);
}

/*
 * Tableau theorem prover algorithm tests whether a propositional formula is satisfiable or unsatisfiable.
 */
bool tableau_algorithm(tree_node* formula)
{
    // Create tableau and initialize tableau with root formula.
    tableau* tableau = tableau_create();
    tableau_init(tableau, formula);

    while (!tableau_empty(tableau))
    {
        theory* set = tableau_dequeue(tableau); // dequeue the next unexpanded root formula from the tableau.
        theory* set1 = NULL;
        theory* set2 = NULL;

        if (theory_fully_expanded(set) && !theory_contradictory(set))
        {
            theory_free(set);
            tableau_free(tableau);
            return true; // original formula is satisfiable.
        }

        tree_node* phi = theory_pick_non_literal(set);
        tree_node* left = NULL;
        tree_node* right = NULL;
        formula_type type = get_formula_type(phi, &left, &right);

        // Expand formula based on type of non-literal (alpha rule for conjunction and beta rule for disjunction).
        switch (type)
        {
            case alpha:
                // The theory is enqueued with the alpha formula replaced by the left and right subformulas.
                theory_push(set, left);
                theory_push(set, right);
                if (!theory_contradictory(set) && !tableau_contains(tableau, set))
                {
                    tableau_enqueue(tableau, set); // enqueue theory if not contradictory and not in the tableau.
                }
                else
                {
                    theory_free(set);
                }
                break;
            case beta:
                // The left subformula is enqueued as a separate theory.
                set1 = theory_copy(set);
                theory_push(set1, left);
                if (!theory_contradictory(set1) && !tableau_contains(tableau, set1))
                {
                    tableau_enqueue(tableau, set1); // enqueue theory if not contradictory and not in the tableau.
                }
                else
                {
                    theory_free(set1);
                }

                // The right subformula is enqueued as a separate theory.
                set2 = theory_copy(set);
                theory_push(set2, right);
                if (!theory_contradictory(set2) && !tableau_contains(tableau, set2))
                {
                    tableau_enqueue(tableau, set2); // enqueue theory if not contradictory and not in the tableau.
                }
                else
                {
                    theory_free(set2);
                }

                theory_free(set);
                break;
            default:
                exit(1);
        }

        tree_free(phi);
    }

    tableau_free(tableau);
    return false; // original formula is not satisfiable.
}

/*
 * Tests whether a formula is satisfiable (true under at least one valuation).
 */
bool is_satisfiable(tree_node* formula)
{
    return tableau_algorithm(formula);
}

/*
 * Tests whether a formula is valid (true under all possible valuations).
 */
bool is_valid(tree_node* formula)
{
    token negated;
    token_init(&negated, negation, '-');
    tree_node* neg_formula = negated_formula(negated, formula);

    bool valid = !is_satisfiable(neg_formula); // ϕ is valid ⟺ -ϕ is unsatisfiable.
    return valid;
}