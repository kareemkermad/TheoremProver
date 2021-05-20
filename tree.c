#include "tree.h"
#include "formula_writer.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <string.h>

/*
 * Creates an isolated binary tree node initialized with a token.
 */
tree_node* tree_node_create(token token)
{
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    node->token = token;
    node->left_child = node->right_child = NULL;
    return node;
}

/*
 * Frees nodes in the binary tree using post-order tree traversal.
 */
void tree_free(tree_node* node)
{
    if (node != NULL)
    {
        tree_free(node->left_child);
        tree_free(node->right_child);
        free(node);
    }
}

/*
 * Checks if two binary trees are equal.
 */
bool tree_equals(tree_node* node1, tree_node* node2)
{
    if (node1 == NULL && node2 == NULL)
    {
        return true; // both trees are empty.
    }

    if (node1 != NULL && node2 != NULL)
    {
        // Both trees are not empty.
        bool b1 = equals(node1->token, node2->token); // checks if the tokens for each root node are equal.
        bool b2 = tree_equals(node1->left_child, node2->left_child); // checks if the left subtrees are equal.
        bool b3 = tree_equals(node1->right_child, node2->right_child); // checks if the right subtrees are equal.
        return b1 && b2 && b3;
    }

    return false; // one tree is empty but the other is not empty.
}

/*
 * Creates a copy of the binary tree using pre-order tree traversal.
 */
tree_node* tree_node_copy(tree_node* node)
{
    if (node != NULL)
    {
        tree_node* copy = tree_node_create(node->token);
        copy->left_child = tree_node_copy(node->left_child);
        copy->right_child = tree_node_copy(node->right_child);
        return copy;
    }

    return NULL;
}

/*
 * Helper function creates a binary tree for negating any formula.
 */
tree_node* negated_formula(token negation, tree_node* formula)
{
    tree_node* node = tree_node_create(negation);
    node->left_child = formula;
    return node;
}

/*
 * Helper function creates a binary tree for a proposition.
 */
tree_node* proposition_formula(token proposition)
{
    return tree_node_create(proposition);
}

/*
 * Helper function creates a binary tree for a binary formula.
 */
tree_node* binary_formula(token binary, tree_node* left_formula, tree_node* right_formula)
{
    tree_node* node = tree_node_create(binary);
    node->left_child = left_formula;
    node -> right_child = right_formula;
    return node;
}

/*
 * Gets the type of the formula (alpha or beta) depending on the structure and type of the root node.
 * Alpha formulas have the form: (A ^ B), -(A v B), -(A > B), --A.
 * Beta formula have the form: (A v B), -(A ^ B), (A > B).
 */
formula_type get_formula_type(tree_node* formula, tree_node** exp1, tree_node** exp2)
{
    tree_node* left = tree_node_copy(formula->left_child);
    tree_node* right = tree_node_copy(formula->right_child);

    token negated;
    token_init(&negated, negation, '-');

    // Ordinary binary formula types.
    char c = formula->token.symbol;
    if (is_and_connective(c))
    {
        // An alpha formula of the form (A ^ B).
        *exp1 = left;
        *exp2 = right;
        return alpha;
    }
    else if (is_or_connective(c))
    {
        // A beta formula of the form (A v B).
        *exp1 = left;
        *exp2 = right;
        return beta;
    }
    else if (is_implies_connective(c))
    {
        // A beta formula of the form (A > B) ≡ (-A v B).
        *exp1 = negated_formula(negated, left);
        *exp2 = right;
        return beta;
    }

    // Negated binary formula types.
    c = formula->left_child->token.symbol;
    if (is_and_connective(c))
    {
        // A beta formula of the form -(A ^ B) ≡ (-A v -B).
        *exp1 = negated_formula(negated, left->left_child);
        *exp2 = negated_formula(negated, left->right_child);
        return beta;
    }
    else if (is_or_connective(c))
    {
        // An alpha formula of the form -(A v B) ≡ (-A ^ -B).
        *exp1 = negated_formula(negated, left->left_child);
        *exp2 = negated_formula(negated, left->right_child);
        return alpha;
    }
    else if (is_implies_connective(c))
    {
        // An alpha formula of the form -(A > B) ≡ (A ^ -B).
        *exp1 = left->left_child;
        *exp2 = negated_formula(negated, left->right_child);
        return alpha;
    }

    // An alpha formula (double negation) of the form --A ≡ A.
    *exp1 = tree_node_copy(left->left_child);
    *exp2 = NULL;
    tree_free(left);
    return alpha;
}