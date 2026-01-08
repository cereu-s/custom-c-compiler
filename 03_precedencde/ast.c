#include "def.h"
#include "data.h"
#include "decl.h"

// generic AST node generator
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue)
{
    struct ASTnode *node;

    // dynamic memory allcation
    node = (struct ASTnode *)malloc(sizeof(struct ASTnode));

    // memory allocation failure
    if (node == NULL)
    {
        fprintf(stderr, "memory allocation failed in mkASTnode()\n");
        exit(1);
    }

    // populating node with values
    node->op = op;
    node->left = left;
    node->right = right;
    node->intValue = intValue;

    return (node);
}


// AST unary node generator - single node
struct ASTnode *mkASTunaryNode(int op, struct ASTnode *left, int intValue)
{
    struct ASTnode *node = mkASTnode(op, left, NULL, intValue);
    return (node);
}


// AST leaf node generator - no child
struct ASTnode *mkASTleafNode(int op, int intValue)
{
    struct ASTnode *node = mkASTnode(op, NULL, NULL, intValue);
    return (node);
}