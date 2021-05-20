#include "tokenizer.h"
#include "token.h"

/*
 * Skips over any whitespace characters in the input formula.
 */
void read_whitespace(const char* formula, int* offset)
{
    while (is_whitespace(formula[*offset])) { ++(*offset); }
}

/*
 * Reads the next symbol in the input formula.
 */
void read_symbol(const char* formula, int* offset, token* token)
{
    char c = formula[*offset];

    if (is_proposition(c))
    {
        // Creates a token for the propositional letter and increments the offset.
        token_init(token, proposition, c);
        ++(*offset);
        return;
    }

    if (is_binary_connective(c))
    {
        // Creates a token for the binary connective and increments the offset.
        token_init(token, binary_connective, c);
        ++(*offset);
        return;
    }

    if (is_negation(c))
    {
        // Creates a token for the negation and increments the offset.
        token_init(token, negation, c);
        ++(*offset);
        return;
    }

    if (is_left_parenthesis(c))
    {
        // Creates a token for the left parenthesis and increments the offset.
        token_init(token, left_parenthesis, c);
        ++(*offset);
        return;
    }

    if (is_right_parenthesis(c))
    {
        // Creates a token for the right parenthesis and increments the offset.
        token_init(token, right_parenthesis, c);
        ++(*offset);
        return;
    }

    token_init(token, end, c); // creates a token for the end of input null character.
}

/*
 * Reads any whitespace characters and the next symbol in the input formula.
 */
void get_token(const char* formula, int* offset, token* token)
{
    read_whitespace(formula, offset);
    read_symbol(formula, offset, token);
}