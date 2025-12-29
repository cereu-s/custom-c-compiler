#include "def.h"
#include "data.h"
#include "decl.h"

// generic AST node generator
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue)
{
    struct ASTnode *n;
    n = (struct ASTnode *)malloc(sizeof(struct ASTnode));

    if (n == NULL)
    {
        fprintf(stderr, "unable to malloc() in mkASTnode()\n");
        exit (1);
    }


    n->op = op;

    n->left = left;
    n->right = right;

    n->intValue = intValue;

    return n;
}

// leaf AST node generator
struct ASTnode *mkASTLeafNode(int op, int intValue)
{
    struct ASTnode *n;
    n = mkASTnode(op, NULL, NULL, intValue);

    return n;
}

// unary AST node generator
struct ASTnode *mkASTUnaryNode(int op, struct ASTnode *left, int intValue)
{
    struct ASTnode *n;
    n = mkASTnode(op, left, NULL, intValue);

    return n;
}