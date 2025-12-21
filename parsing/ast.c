#include "def.h"
#include "data.h"
#include "decl.h"



// generic AST node generator
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue)
{
    struct ASTnode *n;

    // dynamic memory allocation
    n = (struct ASTnode *)malloc(sizeof(struct ASTnode));

    // data entry
    n->op = op;

    n->left = left;
    n->right = right;

    n->intValue = intValue;

    return (n);
}



// AST leaf node generator function
struct ASTnode *mkASTLeafNode(int op, int intValue)
{
    struct ASTnode *n;
    n = mkASTnode(op, NULL, NULL, intValue);
    return (n);
}



// AST unary node generator function
struct ASTnode *mkASTUnaryNode(int op,  struct ASTnode *left)
{
    struct ASTnode *n;
    n = mkASTnode(op, left, NULL, 0);
    return (n);
}