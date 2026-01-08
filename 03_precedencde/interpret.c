#include "def.h"
#include "data.h"
#include "decl.h"

char *ASTopStr[] = {"+", "-", "*", "/"};

// interprets AST tree
int ASTinterpreter(struct ASTnode *node)
{
    int left, right;

    // if left child exists, recursively get its value
    if (node->left)
    {
        left = ASTinterpreter(node->left);
    }

    // if right child exists, recursively get its value
    if (node->right)
    {
        right = ASTinterpreter(node->right);
    }

    // priting opeartions to terminal
    if (node->op == A_INTLIT)
    {
        printf("INTLIT: %d\n", node->intValue);
    }
    else
    {
        printf("%d %s %d\n", left, ASTopStr[node->op], right);
    }

    // returning recursive call with opeartion between childs
    switch (node->op)
    {
    case A_ADD:
        return left + right;
    case A_SUB:
        return left - right;
    case A_MUL:
        return left * right;
    case A_DIV:
        return left / right;

    // base case
    case A_INTLIT:
        return node->intValue;
    
    default:
        // unknown operation error
        fprintf(stderr, "unknown AST operation %d\n", node->op);
        exit(1);
    }
}