#ifndef extern_
#define extern_ extern
#endif

// only main defines extern_, resulting in all global variables belonging to main
// other file may use these variables as extern


// global variable
;
extern_ int putback;
extern_ int line;
extern_ FILE *inFile;

extern_ struct Token token;