#include "def.h"
#include "data.h"
#include "decl.h"

// token to AST type converter
static int ASTop(int op)
{
    switch (op)
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
        printf("%d %d\n\n", token.token, token.intValue);
        fprintf(stderr, "unknown AST operation '%c' in ASTop()\n", token.token);
        exit(1);
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
        exit(1);
    }
}



// tight binds operators with higher precendence
static struct ASTnode *multiplicative_expr(void)
{
    struct ASTnode *left, *right;

    // gets the primary leaf node
    left = primary();

    // gets the next operational token
    scan(&token);

    while(token.token == T_STAR || token.token == T_SLASH)
    {
        // stores the operation
        int op = token.token;

        // gets next primary token
        scan(&token);

        // recursively gets the rest of the tokens on the right child
        right = multiplicative_expr();

        left = mkASTnode(op, left, right, 0);
    }

    return left;
}



// joins higher precedence operations together
struct ASTnode *additive_expr(void)
{
    struct ASTnode *left, *right;

    // gets the left multiplicative expr
    left = multiplicative_expr();

    // at this level, its either an operational token or EOF
    if (token.token == T_EOF)
    {
        return left;
    }

    // rest of the additive expr is connected recursively on the right child
    while(1)
    {
        // stores the operational token
        int op = token.token;

        // scans the next primary token
        scan(&token);

        right = multiplicative_expr();

        left = mkASTnode(op, left, right, 0);

        if (token.token == T_EOF)
        {
            break;
        }
    }

    return left;
}