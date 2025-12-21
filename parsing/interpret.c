#include "def.h"
#include "data.h"
#include "decl.h"

// terminals to be printed to the output stream
char* ASTtok[] = {"+", "-", "*", "/"};

int ASTinterpret(struct ASTnode *n)
{
    int left, right;

    // if left node, recursively get the value
    if (n->left)
    {
        left = ASTinterpret(n->left);
    }

    // if right node, recursively get the value
    if (n->right)
    {
        right = ASTinterpret(n->right);
    }

    if (n->op == A_INTLIT)
    {
        printf("INT \t%d\n", n->intValue);
    }
    else
    {
        printf("%d %s %d\n", left, ASTtok[n->op], right);
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
        return (n->intValue);
    
    default:
        fprintf(stderr, "unknown AST operation %d\n", n->op);
        exit(1);
    }
}