#include "def.h"

// as extern_ was defined, all global variables belond to main, others will obtain as extern
#define extern_
#include "data.h"
#undef extern_

#include "decl.h"



// sets initial condition
void init()
{
    putback = '\n';
    line = 1;
}



// msg for usage error
void usageError(char *prog)
{
    printf("usage: %s inFile\n", prog);
    exit(1);
}



// opens file in global file ptr
void openFile(char* fileName)
{
    inFile = fopen(fileName, "r");

    if (inFile == NULL)
    {
        fprintf(stderr, "error opening file: '%s'\n", fileName);
        exit(1);
    }
}


// parses file
void scanFile(void)
{
    // get initial token
    scan(&token);

    // generate AST tree
    struct ASTnode *n = ASTgen();

    // interpret AST tree
    int result = ASTinterpret(n);

    printf("result: %d\n", result);
}

int main(int argc, char *argv[])
{
    // setting initial condition
    init();

    // usage error
    if (argc != 2)
    {
        usageError(argv[0]);
    }

    // opens file in file ptr
    openFile(argv[1]);

    // scans the file
    scanFile();

    return 0;
}