#include "def.h"
#include "data.h"
#include "decl.h"

// coverts token types to AST operations
int arithOp(int token)
{
    switch (token)
    {
    case T_PLUS:
        return (A_ADD);
    case T_MINUS:
        return (A_SUB);
    case T_STAR:
        return (A_MUL);
    case T_SLASH:
        return (A_DIV);

    default:
        fprintf(stderr, "unknown AST type in arithOp() on line %d\n", line);
        exit(1);
    }
}

// scans a primary token and returns a leaf AST node
// NOTE: the primary token is always an INTLIT

static struct ASTNode *primary(void)
{
    struct ASTNode *n;

    if (token.token == T_INTLIT)
    {
        n = mkASTleafNode(A_INTLIT, token.intValue);

        // scans next operation token
        scan(&token);
    }
    // else if (token.token == T_EOF)
    // {
    //     // empty input stream
    //     printf("empty file\n");
    //     exit(0);
    // }
    else
    {
        fprintf(stderr, "syntax error on line %d\n", line);
        exit(1);
    }

    return (n);
}


struct ASTNode *binExpr(void)
{
    struct ASTNode *n, *left, *right;

    // get the primary token on the left branch
    left = primary();

    // reached end of file
    if (token.token == T_EOF)
    {
        return (left);
    }

    int op = arithOp(token.token);

    // scans next INTLIT token
    scan(&token);

    // recursively parse the right branch
    right = binExpr();

    // generate an AST node using left and right branch
    n = mkASTNode(op, left, right, 0);

    return (n);
}
