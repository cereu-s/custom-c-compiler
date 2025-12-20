#include "def.h"
#include "data.h"
#include "decl.h"

// returns position of char in a string
static int charPos(char *str, int c)
{
    char *pos = strchr(str, c);
    return (pos ? pos - str : -1);
}

// puts back char back in the input stream
static void putbackChar(int c)
{
    putback = c;
}

// gets next char from the input stream
static int next(void)
{
    int c;

    // a char left in the input stream
    if (putback)
    {
        c = putback;
        putback = 0;
        return c;
    }

    // get char from file
    c = fgetc(inFile);

    // newline encountered
    if (c == '\n')
    {
        line++;
    }

    return c;
}

// skips unwanted char from the input
static int skip(void)
{
    int c;

    c = next();

    // skips input while unwanted char
    while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
    {
        c = next();
    }

    return c;
}

// scans a whole integer
static int scanInt(int c)
{
    int k, val = 0;
    while ((k = charPos("0123456789", c)) >= 0)
    {
        val = val * 10 + k;
        c = next();
    }

    // found a non int char
    // put it back in the input stream
    putbackChar(c);

    return val;
}

// scans a valid token
int scan(struct Token *t)
{
    int c;

    // get first valid char
    c = skip();

    switch (c)
    {
    case EOF:
        // reached end of file, no token found
        return 0;

    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c))
        {
            t->token = T_INTLIT;
            t->intValue = scanInt(c);
        }
        else
        {
            // invalid token
            fprintf(stderr, "unrecognized char '%c' on line %d\n", c, line);
            exit(1);
        }
    }

    // a token was found
    return (1);
}