#include "def.h"
#include "data.h"
#include "decl.h"

// token to AST operator conversion
static int ASTop(int tok)
{
    switch (tok)
    {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUB;
    case T_STAR:
        return A_MUL;
    case T_SLASH:
        return A_DIV;

    case T_INTLIT:
        return A_INTLIT;
    
    default:
        fprintf(stderr, "cannot convert token: '%c' to AST operation in ASTop()\n", tok);
        exit(1);
    }
}

// returns a primary token
// NOTE: a primary token is always an INTLIT
static struct ASTnode *primary(void)
{
    struct ASTnode *node;

    if (token.token == T_INTLIT)
    {
        int op = ASTop(token.token);
        int intValue = token.intValue;

        // generate leaf AST node
        node = mkASTleafNode(op, intValue);

        return (node);
    }
    else
    {
        // syntax error encountered, wrong operator / operand ordering
        fprintf(stderr, "syntax error on line %d\n", line);
        exit(1);
    }
}

struct ASTnode *ASTgen(void)
{
    struct ASTnode *node, *left, *right;

    // gets the first primary token in the left child
    left = primary();

    // gets the next operational token
    scan(&token);

    // reached end of file
    if(token.token == T_EOF)
    {
        // return the left child
        return left;
    }

    // stores the current operation (convert from token to AST operation)
    int op = ASTop(token.token);

    // gets the next primary token for next iteration of the recursive call
    scan(&token);

    // recursively gets the rest of the tree in the right child
    right = ASTgen();

    // generate operational AST node with left and right child as operands
    // NOTE: since operational AST node, intvalue is NA
    node = mkASTnode(op , left, right, 0);

    return (node);
}