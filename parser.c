#include "parser.h"
#include "tokenizer.h"
#include <stdlib.h>

/*
 * Helper function for parsing a binary formula.
 */
tree_node* parse_binary_formula(char* formula, int* offset, token* current_token)
{
    tree_node* left_formula;
    tree_node* right_formula;
    token binary_token;

    left_formula = parse_formula(formula, offset, current_token);

    get_token(formula, offset, current_token);
    binary_token = *current_token;

    if (left_formula != NULL && binary_token.type == binary_connective)
    {
        right_formula = parse_formula(formula, offset, current_token);
        if (right_formula != NULL)
        {
            get_token(formula, offset, current_token);
            if (current_token->type == right_parenthesis)
            {
                return binary_formula(binary_token, left_formula, right_formula);
            }

            if (current_token->type == end)
            {
                --(*offset);
            }
        }
    }

    return NULL;
}

/*
 * Helper function for parsing a negated formula.
 */
tree_node* parse_negated_formula(char* formula, int* offset, token* current_token)
{
    token negation = *current_token;
    tree_node* left_formula = parse_formula(formula, offset, current_token);

    if (left_formula != NULL)
    {
        return negated_formula(negation, left_formula);
    }

    return NULL;
}

/*
 * Helper function for parsing a propositional formula.
 */
tree_node* parse_formula(char* formula, int* offset, token* current_token)
{
    get_token(formula, offset, current_token);

    switch (current_token->type)
    {
        case proposition:
            return proposition_formula(*current_token);
        case negation:
            return parse_negated_formula(formula, offset, current_token);
        case left_parenthesis:
            return parse_binary_formula(formula, offset, current_token);
        case end:
            --(*offset);
            return NULL;
        default:
            return NULL;
    }
}

/*
 * Parses the propositional formula as a binary tree.
 */
tree_node* parse(char* formula)
{
    int offset = 0;
    token* current_token = token_alloc();

    tree_node* node = parse_formula(formula, &offset, current_token);

    if (node == NULL) { return NULL; }

    get_token(formula, &offset, current_token);
    if (!is_end(current_token->symbol))
    {
        return NULL;
    }

    token_free(current_token);

    return node;
}