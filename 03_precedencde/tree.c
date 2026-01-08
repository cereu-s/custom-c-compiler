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

    // logic testing
    // printf("token: %d\t value: %d\n", token.token, token.intValue);

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

// multipicative exprexssion tree generator
static struct ASTnode *multiplicativeExpr(void)
{
    struct ASTnode *left, *right;

    // gets a primary token on left child
    left = primary();

    // gets the next operational token
    scan(&token);

    // reached end of file
    if (token.token == T_EOF)
    {
        return left;
    }

    // parses a whole multiplicative expr recursively and generates tree
    while (token.token == T_STAR || token.token == T_SLASH)
    {

        // stores the current operation
        int op = ASTop(token.token);

        // scans the next primary token
        scan(&token);

        // gets the right child recursively
        right = multiplicativeExpr();

        // generates tree on the left child
        left = mkASTnode(op, left, right, 0);

        // reached end of file
        if (token.token == T_EOF)
        {
            break;
        }
    }

    // at this level, an extra operational token was scanned
    // which is either additive operator or EOF

    return (left);
}

// additive expression tree generator
struct ASTnode *additiveExpr(void)
{
    struct ASTnode *left, *right;

    left = multiplicativeExpr();

    // reached end of file
    if (token.token == T_EOF)
    {
        return (left);
    }

    while (1)
    {

        // stores current operation
        // NOTE: at this level, the operator is always an additive opeartor
        int op = ASTop(token.token);

        // scans the next primary token
        scan(&token);

        // recursively gets the right child
        right = multiplicativeExpr();

        // merges into left child
        left = mkASTnode(op, left, right, 0);

        if (token.token == T_EOF)
        {
            break;
        }
    }

    return (left);
}