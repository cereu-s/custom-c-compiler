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


// file scanner for tokenizaition
static void scanFile(void)
{
    // scanning initial primary token
    scan(&token);

    // generating AST tree
    struct ASTnode *n = treeGen();

    // interpreting AST tree
    int ans = ASTinterpreter(n);

    // printing result on terminal
    printf("result: %d\n", ans);
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