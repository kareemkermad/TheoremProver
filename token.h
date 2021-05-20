#ifndef THEOREMPROVER_TOKEN_H
#define THEOREMPROVER_TOKEN_H

#include <stdbool.h>

/*
 * Token type represents the type of token making up a propositional formula.
 */
typedef enum token_type
{
    left_parenthesis,
    right_parenthesis,
    proposition,
    binary_connective,
    negation,
    end
} token_type;

/*
 * A token has a type and a symbol.
 */
typedef struct token
{
    token_type type;
    char symbol;
} token;

token* token_alloc();

void token_init(token* token, token_type type, char symbol);

void token_free(token* token);

bool equals(token token1, token token2);

#endif //THEOREMPROVER_TOKEN_H
