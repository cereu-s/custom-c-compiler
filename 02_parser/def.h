#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// terminal tokens
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

// AST node types
enum
{
    A_ADD,
    A_SUB,
    A_MUL,
    A_DIV,
    A_INTLIT
};

// AST node structure
struct ASTnode
{
    struct ASTnode *left, *right;       // left and right child
    int op;                             // corresponding operation between the childs
    int intValue;                       // value, in case of INTLIT
}