#include "def.h"
#include "data.h"
#include "decl.h"

// token to AST type converter
static int ASTop(int token)
{
    switch (token)
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
        fprintf(stderr, "unknown AST operation '%c' in ASTop()\n", token);
        exit (1);
    }
}

// parses a primary token
// NOTE: a primary token is always an integer
static struct ASTnode *primary(void)
{
    struct ASTnode *n;

    if (token.token == T_INTLIT)
    {
        n = mkASTLeafNode(ASTop(token.token), token.intValue);
        return n;
    }
    else
    {
        fprintf(stderr, "syntax error on line %d\n", line);
        exit (1);
    }
}

struct ASTnode *treeGen(void)
{
    struct ASTnode *n, *left, *right;

    // left child contains the primary token
    left = primary();

    // scanning next token
    // NOTE: token must be an operation
    scan(&token);

    // reached end of file
    if (token.token == T_EOF)
    {
        return left;
    }

    // Token to AST operation conversion
    int op = ASTop(token.token);

    // scanning next primary token
    scan(&token);

    // right child generates the remaining tree recursively
    right = treeGen();

    n = mkASTnode(op, left, right, 0);

    return n;
}
