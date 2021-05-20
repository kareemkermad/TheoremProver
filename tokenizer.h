#ifndef THEOREMPROVER_TOKENIZER_H
#define THEOREMPROVER_TOKENIZER_H

#include <stdbool.h>

typedef struct token token;

/*
 * Checks if the character is a whitespace.
 */
static inline bool is_whitespace(char c)
{
    return c == ' ' || c == '\t';
}

/*
 * Checks if the character is a propositional letter.
 */
static inline bool is_proposition(char c)
{
    return c == 'p' || c == 'q' || c == 'r' || c == 'x' || c == 'y' || c == 'w'; // prop ::= p | q | r | x | y | w
}

/*
 * Checks if the character is a logical binary connective.
 */
static inline bool is_binary_connective(char c)
{
    return c == 'v' || c == '^' || c == '>'; // binary ::= v | ^ | >
}

/*
 * Checks if the character is a logical conjunction.
 */
static inline bool is_and_connective(char c)
{
    return c == '^';
}

/*
 * Checks if the character is a logical disjunction.
 */
static inline bool is_or_connective(char c)
{
    return c == 'v';
}

/*
 * Checks if the character is a logical implication.
 */
static inline bool is_implies_connective(char c)
{
    return c == '>';
}

/*
 * Checks if the character is a logical negation.
 */
static inline bool is_negation(char c)
{
    return c == '-';
}

/*
 * Checks if the character is an open parenthesis.
 */
static inline bool is_left_parenthesis(char c)
{
    return c == '(';
}

/*
 * Checks if the character is a closed parenthesis.
 */
static inline bool is_right_parenthesis(char c)
{
    return c == ')';
}

/*
 * Checks for an end of input null character.
 */
static inline bool is_end(char c)
{
    return c == '\0';
}

void read_whitespace(const char* formula, int* offset);

void read_symbol(const char* formula, int* offset, token* token);

void get_token(const char* formula, int* offset, token* token);

#endif //THEOREMPROVER_TOKENIZER_H
