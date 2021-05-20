#include <stdlib.h>
#include <string.h>

#include "formula_writer.h"
#include "tree.h"

/*
 * Calculates the number of characters required to represent the formula as a character array.
 */
int formula_length(tree_node* node)
{
    if (node != NULL)
    {
        switch (node->token.type)
        {
            case proposition:
                return 1;
            case negation:
                return 1 + formula_length(node->left_child);
            case binary_connective:
                return 3 + formula_length(node->left_child) + formula_length(node->right_child);
            default:
                exit(1);
        }
    }

    return 0;
}

/*
 * Appends a character to the end of the character array.
 */
void append(char** s, char c)
{
    char* t = *s;
    size_t n = strlen(t);
    t[n++] = c;
    t[n] = '\0';
}

/*
 * Converts the propositional formula represented as a binary tree to a character array in infix notation.
 */
void infix(tree_node* node, char** formula)
{
    if (node != NULL)
    {
        token token = node->token;
        switch (token.type)
        {
            case proposition:
                append(formula, token.symbol);
                break;
            case negation:
                append(formula, token.symbol);
                infix(node->left_child, formula);
                break;
            case binary_connective:
                append(formula, '(');
                infix(node->left_child, formula);
                append(formula, token.symbol);
                infix(node->right_child, formula);
                append(formula, ')');
                break;
            default:
                return;
        }
    }
}