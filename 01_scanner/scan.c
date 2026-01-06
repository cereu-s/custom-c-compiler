#include "def.h"
#include "data.h"
#include "decl.h"


// stores extra scanned char's for later use
void putbackChar(int ch)
{
    putback = ch;
}


// scans the next char
static int next(void)
{
    int ch;

    // extra char left for use
    if (putback)
    {
        ch = putback;
        putback = 0;

        return (ch);
    }

    // gets the next char from input file
    ch = fgetc(inFile);

    // newline encountered
    if (ch == '\n')
    {
        line++;
    }

    return (ch);
}


// skips unwanted char's (newline, tab etc.)
static int skip(void)
{
    int ch;
    ch = next();

    // skips while unwanted char is encountered
    while (ch == ' ' || ch == '\n' || ch == '\t')
    {
        ch = next();
    }

    // a valid token was found
    return (ch);
}


// returns position of char in a string
static int strPos(char* str, int ch)
{
    // returns pointer to where the char matches the string
    char* pos = strchr(str, ch);

    return (pos ? pos - str : -1);
}


// scans a whole integer from char stream
static int scanInt(int ch)
{
    int parsedValue = 0, digit;

    // loop while integer char is encountered
    while ((digit = strPos("0123456789", ch)) >= 0)
    {
        parsedValue *= 10;
        parsedValue += digit;

        ch = next();
    }

    // a non-integer char was encountered
    // stored for later use
    putbackChar(ch);

    return (parsedValue);
}

// global token scanner function
int scan(struct Token *tok)
{
    int ch;

    ch = skip();

    switch (ch)
    {
    case EOF:
        // reached end of file
        // no token was found
        return (0);
    
    case '+':
        tok->token = T_PLUS;
        break;
    case '-':
        tok->token = T_MINUS;
        break;
    case '*':
        tok->token = T_STAR;
        break;
    case '/':
        tok->token = T_SLASH;
        break;
    
    default:
        if (isdigit(ch))
        {
            tok->token = T_INTLIT;
            tok->intValue = scanInt(ch);
        }
        else
        {
            // unrecognized token encountered
            fprintf(stderr, "unrecognized char '%c' on line: %d\n", ch, line);
            exit(1);
        }
    }

    // a valid token was found
    return (1);
}