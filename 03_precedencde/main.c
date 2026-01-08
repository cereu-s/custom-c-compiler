#include "def.h"

// defined extern_, resulting all global variables to belong to main
#define extern_
#include "data.h"
#undef extern_

#include "decl.h"


// sets up initial condition
static void init(void)
{
    putback = '\n';
    line = 1;
}


// prog usage error: prints msg and exits
static void progUsageErr(char* prog)
{
    fprintf(stderr, "usage: %s inFile\n", prog);
    exit(1);
}


// sets up input file ptr with error handling if any
static void fileSetter(char* file)
{
    inFile = fopen(file, "r");

    if (inFile == NULL)
    {
        fprintf(stderr, "error opening file: '%s'\n", file);
        exit(1);
    }
}


// scans input for tokens, prints terminals
static void scanFile(void)
{
    // scans an initial primary token
    scan(&token);

    // generate AST tree
    struct ASTnode *tree = ASTgen();

    // interpret the AST tree
    int result = ASTinterpreter(tree);

    // printing result to terminal
    printf("result: %d\n", result);
}


// main function
int main(int argc, char* argv[])
{
    // passing wrong number of arguments
    if (argc != 2)
    {
        progUsageErr(argv[0]);
    }

    // file setup;
    fileSetter(argv[1]);

    // initial condition setup
    init();

    // scanning input for tokens
    scanFile();


    return 0;
}