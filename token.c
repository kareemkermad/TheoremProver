#include <stdlib.h>
#include "token.h"

/*
 * Allocates memory for a token.
 */
token* token_alloc()
{
    return (token*)malloc(sizeof(token));
}

/*
 * Initializes a token with a token type and symbol.
 */
void token_init(token* token, token_type type, char symbol)
{
    token->type = type;
    token->symbol = symbol;
}

/*
 * Frees a token.
 */
void token_free(token* token)
{
    free(token);
}

/*
 * Checks whether two tokens are equal (have the same type and the same symbol).
 */
bool equals(token token1, token token2)
{
    bool b1 = token1.type == token2.type;
    bool b2 = token1.symbol == token2.symbol;
    return b1 && b2;
}