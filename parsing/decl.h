int scan(struct Token *t);

// AST generator functions
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue);
struct ASTnode *mkASTLeafNode(int op, int intValue);
struct ASTnode *mkASTUnaryNode(int op,  struct ASTnode *left);

// AST tree generator
struct ASTnode *ASTgen(void);

// AST tree
int ASTinterpret(struct ASTnode *n);
