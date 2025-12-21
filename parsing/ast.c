#include "def.h"
#include "data.h"
#include "decl.h"

// AST node generator function definitions



// generic AST node generator
struct ASTNode *mkASTNode(int op, struct ASTNode *left, struct ASTNode *right, int intValue)
{
    struct ASTNode *n;

    // dynamic memory allocation
    n = (struct ASTNode *)malloc(sizeof(struct ASTNode));

    // assigning values
    n->op = op;

    n->left = left;
    n->right = right;

    n->intValue = intValue;

    return (n);
}

// leaf AST node generator
struct ASTNode *mkASTleafNode(int op, int intValue)
{
    return mkASTNode(op, NULL, NULL, intValue);
}

// unary AST node generator
struct ASTNode *mkASTUnaryNode(int op, struct ASTNode *left, int intValue)
{
    return mkASTNode(op, left, NULL, intValue);
}
