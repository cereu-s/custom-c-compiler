#include "def.h"
#include "data.h"
#include "decl.h"

// puts unused char back in the input stream
static void putbackChar(int c)
{
    putback = c;
}

// gets the next char from the input stream
static int next(void)
{
    int c;

    // if char left in the input stream, returns it
    if (putback)
    {
        c = putback;
        putback = 0;

        return c;
    }

    c = getc(inFile);

    if (c == '\n')
    {
        line++;
    }

    return c;
}

// skips unwanted char like whitespace, newline etc.
static int skip(void)
{
    int c;
    c = next();

    // skips while valid char is found
    while (c == ' ' || c == '\n' || c == '\t' || c == '\f')
    {
        c = next();
    }

    return c;
}

// returns char position in a string
static int chrPos(char *str, int c)
{
    char *p;
    p = strchr(str, c);

    return (p ? p - str : -1);
}

// scans a whole integer from char stream
static int scanInt(int c)
{
    int val = 0, k;

    while ((k = chrPos("0123456789", c)) >= 0)
    {
        val *= 10;
        val += k;

        // gets the next char
        c = next();
    }

    // a non-integer char was scanned
    // put it back in the input stream
    putbackChar(c);

    return val;
}

// global token scanner
int scan(struct Token *t)
{
    int c;

    c = skip();

    switch (c)
    {
    case EOF:
        t->token = T_EOF;
        break;

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
        // an integer was found
        if (isdigit(c))
        {
            t->token = T_INTLIT;
            t->intValue = scanInt(c);
        }
        else
        {
            // syntax error, unrecognized char
            fprintf(stderr, "unrecognized char '%c' on line %d\n", c, line);
            exit(1);
        }
    }

    // a valid token was found
    return 1;
}
