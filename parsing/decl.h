// token scanner
int scan(struct Token *t);

// AST generator functions
struct ASTNode *mkASTNode(int op, struct ASTNode *left, struct ASTNode *right, int intValue);
struct ASTNode *mkASTleafNode(int op, int intValue);
struct ASTNode *mkASTUnaryNode(int op, struct ASTNode *left, int intValue);

// expression parser
struct ASTNode *binExpr(void);

// AST interpreter
int interpretAST(struct ASTNode *n);