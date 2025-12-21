# Scanning tokens from input stream

## Structure definition
at first we define the structure for token
 in `def.h`
```c
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
```

<br>


## Global variables
the `data.h` file contains  global variables to be used by al files. the variables are defined with keyword **extern_** unless defined. Only the `main.c` file will define **extern_**, making sure that the variables remain to the main file, whereas others will inherit it as extern.

```c
#ifndef extern_
    #define extern_ extern
#endif

// declarations for global variables

extern_ int putback;
extern_ int line;
extern_ FILE *inFile;
```
<br>

## Function declarations
The `decl.h` file contains global function declarations. Only these functions can be accessed globally. Infile functions are defined as static to ensure safety.

```c
int scan(struct Token *t);
```
<br><hr>



The `next()` function gets the next char from the input stream.

```c
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
```
<br><hr>



The `skip()` function skips unwanted characters such as whitespace newline etc.

```c 
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
```
<br><hr>



The `scanInt()` function parses a whole integer.

```c 
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
```
<br>

While parsing a integer, we may read too far into the stream. the `putbackChar()` function puts the extra char back in the input stream by storing it in  a variable to be used by the `next()` function.

```c
static void putbackChar(int c)
{
    putback = c;
}
```
<br><hr>



Finally, the globally defined `scan()` function scans each valid token and returns true if found.

```c
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
```

<br><hr>

in the `main.c` file, we use the `scanFile()` function to parse each valid token and print it in the output stream.

```c
char *tokenStr[] = {"+", "-", "*", "/", "integer"};
```

```c
void scanFile(void)
{
    struct Token t;
    while (scan(&t))
    {
        printf("token: '%s'", tokenStr[t.token]);

        if (t.token == T_INTLIT)
        {
            printf("\t value: %d", t.intValue);
        }

        printf("\n");
    }
}
```


## Testing

input: `in01`

```
1 + 5 - 5 / 12 * 7
```

Output:
```
token: 'integer'         value: 1
token: '+'
token: 'integer'         value: 5
token: '-'
token: 'integer'         value: 5
token: '/'
token: 'integer'         value: 12
token: '*'
token: 'integer'         value: 7
```
<br><hr>

input: `in02`
```
12 * / 5 + 1
- 7     /
2
```

Output:
```
token: 'integer'         value: 12
token: '*'
token: '/'
token: 'integer'         value: 5
token: '+'
token: 'integer'         value: 1
token: '-'
token: 'integer'         value: 7
token: '/'
token: 'integer'         value: 2
```

**Note:** successfully skipped whitespaces and nenwlines.

<br><hr>

input `in03`:

```
12 * 5 / 23

+ 12 * test
```

Output:

```
token: 'integer'         value: 12
token: '*'
token: 'integer'         value: 5
token: '/'
token: 'integer'         value: 23
token: '+'
token: 'integer'         value: 12
token: '*'
unrecognized char 't' on line 3
```
<br><hr>



Next chapter [token parsing](../parsing/readme.md).