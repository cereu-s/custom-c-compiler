#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// enum for tokens
enum
{
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INTLIT,
    T_EOF
};

// token structure
struct Token
{
    int token;
    int intValue;
};

// enum for AST
enum
{
    A_ADD,
    A_SUB,
    A_MUL,
    A_DIV,
    A_INTLIT
};

// AST node structure
struct ASTNode
{
    struct ASTNode *left, *right;
    int op;
    int intValue;
};