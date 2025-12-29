// global function prototypes

int scan(struct Token *t);

// AST node generators
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue);
struct ASTnode *mkASTLeafNode(int op, int intValue);
struct ASTnode *mkASTUnaryNode(int op, struct ASTnode *left, int intValue);

// AST tree generator
struct ASTnode *treeGen(void);

// tree interpreter
int ASTinterpreter(struct ASTnode *t);