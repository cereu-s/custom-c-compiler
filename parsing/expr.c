#include "def.h"
#include "data.h"
#include "decl.h"


// token to AST operation conversion
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
        fprintf(stderr, "unknown token in ASTop() on line %d\n", line);
        exit(1);
    }
}


// scan a primary token
// NOTE: primary token must be INTLIT
static struct ASTnode *primary(void)
{
    struct ASTnode *n;

    if (token.token == T_INTLIT)
    {
        n = mkASTLeafNode(A_INTLIT, token.intValue);

        // scan next operation token
        scan(&token);
    }
    else
    {
        fprintf(stderr, "syntax error on line %d\n", line);
        exit(1);
    }

    return (n);
}

struct ASTnode *ASTgen(void)
{
    struct ASTnode *n, *left, *right;

    left = primary();

    // end of file reached
    if (token.token == T_EOF)
    {
        return (left);
    }

    int op = ASTop(token.token);

    // scan next INTLINT
    scan(&token);

    right = ASTgen();

    n = mkASTnode(op, left, right, 0);

    return (n);
}
