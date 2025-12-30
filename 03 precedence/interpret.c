#include "def.h"
#include "data.h"
#include "decl.h"

char *ASTstr[] = {"+", "-", "*", "/"};


int ASTinterpreter(struct ASTnode *n)
{
    int left, right;

    // if left child, get its value recursively
    if (n->left)
    {
        left = ASTinterpreter(n->left);
    }

    // if right child, get its value recursively
    if (n->right)
    {
        right = ASTinterpreter(n->right);
    }

    // printing operations on terminal
    if (n->op == A_INTLIT)
    {
        printf("INTLIT %d\n", n->intValue);
    }
    else
    {
        printf("%d %s %d\n", left, ASTstr[n->op], right);
    }

    
    switch (n->op)
    {
    case A_ADD:
        return left + right;
    case A_SUB:
        return left - right;
    case A_MUL:
        return left * right;
    case A_DIV:
        return left / right;

    case A_INTLIT:
        return n->intValue;

    default:
        fprintf(stderr, "unknown AST operation %d\n", n->op);
        exit (1);
    }
}
