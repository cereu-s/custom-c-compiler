// global function prototypes

// token scanner
int scan(struct Token *t);

// AST node generators
struct ASTnode *mkASTnode(int op, struct ASTnode *left,struct ASTnode *right, int intValue);
struct ASTnode *mkASTunaryNode(int op, struct ASTnode *left, int intValue);
struct ASTnode *mkASTleafNode(int op, int intValue);

// AST tree generator
struct ASTnode *ASTgen(void);

// AST tree interpreter
int ASTinterpreter(struct ASTnode *node);