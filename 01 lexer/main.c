#include "def.h"

// extern_ was defined, therefore all global variables belong to the main file
#define extern_
#include "data.h"
#undef extern_

#include "decl.h"

// setting up initial condition
static void init(void)
{
    putback = '\n';
    line = 1;
}

// usage msg printer
static void errMsg(char *prog)
{
    fprintf(stderr, "usage: %s inFile\n", prog);
    exit(1);
}

// setting file pointer
static void fileSetter(char *file)
{
    inFile = fopen(file, "r");

    // error opening file
    if (inFile == NULL)
    {
        fprintf(stderr, "error opening file '%s'\n", file);
        exit(1);
    }
}

// printing tokens on terminal using scanner
char *tokenStr[] = {"+", "-", "*", "/", "INTLIT"};

// file scanner for tokenizaition
static void scanFile(void)
{
    struct Token t;

    while (scan(&t))
    {
        printf("token: %s", tokenStr[t.token]);

        if (t.token == T_INTLIT)
        {
            printf("\tvalue: %d", t.intValue);
        }

        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    // wrong number of arguments
    if (argc != 2)
    {
        errMsg(argv[0]);
    }

    // setting up file ptr
    fileSetter(argv[1]);

    // setting up initial condition
    init();

    // scanning file
    scanFile();

    exit (0);
}