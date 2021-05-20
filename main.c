#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "formula_writer.h"
#include "tableaux.h"

int max_len = 256; // maximum length of formulas.

/*
 * Parses the input formula and runs the tableau theorem prover algorithm to test for satisfiability/validity.
 */
void theorem_prover(char* formula)
{
    // parse the input formula.
    tree_node* node = parse(formula);

    if (node != NULL)
    {
        char* left;
        char* right;

        switch (node->token.type)
        {
            case proposition:
                printf("%s is a proposition.\n", formula);
                break;
            case negation:
                printf("%s is a negation.\n", formula);
                break;
            case binary_connective:
                left = (char*)malloc(formula_length(node->left_child) * sizeof(char));
                right = (char*)malloc(formula_length(node->right_child) * sizeof(char));
                left[0] = right[0] = '\0';
                infix(node->left_child, &left);
                infix(node->right_child, &right);
                printf("%s is a binary. The left subtree is %s and the right subtree is %s\n", formula, left, right);
                free(left);
                free(right);
                break;
            default:
                exit(1);
        }

        // run the tableau theorem prover algorithm.
        bool check_validity = false;
        printf("Check Valid or Satisfiable? (v/s):\n");
        char response = (char)fgetc(stdin);
        if (response == 'v') { check_validity = true; }
        while (fgetc(stdin) != '\n');

        if (check_validity)
        {
            bool valid = is_valid(node); // test the formula for validity.
            if (valid)
            {
                printf("%s is valid.\n", formula);
            }
            else
            {
                printf("%s is not valid.\n", formula);
            }
        }
        else
        {
            bool satisfiable = is_satisfiable(node); // test the formula for satisfiability.
            if (satisfiable)
            {
                printf("%s is satisfiable.\n", formula);
            }
            else
            {
                printf("%s is not satisfiable.\n", formula);
            }
        }
    }
    else
    {
        printf("%s is not a propositional formula.\n", formula);
    }
}

int main()
{
    while (true)
    {
        // get the user input.
        char formula[max_len];
        printf("Enter propositional formula:\n");
        fgets(formula, max_len, stdin);
        formula[strcspn(formula, "\n")] = 0;

        theorem_prover(formula); // parse formula, build tableau and run the tableau theorem prover.

        // ask user if they want to exit the program.
        printf("Want to exit? (y/n)\n");
        char response = (char)fgetc(stdin);
        if (response == 'y') { break; }
        while (fgetc(stdin) != '\n');
    }
}