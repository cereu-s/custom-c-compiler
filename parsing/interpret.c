#include "def.h"
#include "data.h"
#include "decl.h"

char *ASTop[] = {"+", "-", "*", "/"};

int interpretAST(struct ASTNode *n)
{
    int left, right;

    // if left node, recursively gets the left value
    if (n->left)
    {
        left = interpretAST(n->left);
    }

    // if right node, recursively gets the left value
    if (n->right)
    {
        right = interpretAST(n->right);
    }

    // printing operations on the output stream
    if (n->op == A_INTLIT)
    {
        printf("int %d\n", n->intValue);
    }
    else
    {
        printf("%d %s %d\n", left, ASTop[n->op], right);
    }

    // operation output
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
        exit(1);
    }
}