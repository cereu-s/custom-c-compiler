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
    T_INTLIT
};

// token structure
struct Token
{
    int token;
    int intValue;
};