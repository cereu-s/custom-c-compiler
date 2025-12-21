# Parsing and interpreting the input stream
At this point, we are able to identify tokens. Now the input has to be checked syntactically. 



## Language grammar

To check syntax, grammatical rules are needed. A `BNF Table` will provide us with the necessary grammar to check for correct syntax.
<br>

The following BNF table is used for our current purpose

```
<Expression> :    <Number>
                | <Expression> '+' <Expression>
                | <Expression> '-' <Expression>
                | <Expression> '*' <Expression>
                | <Expression> '/' <Expression>
                ;

<Number> :        T_INTLIT
                ;                
```
<br>



## Parse tree generation

Using the `BNF Table`, we can parse the input stream and generate a parse tree. We may use `Recursive Descent Parser` to generate the parse tree. The parsing process goes as follows:

**Pseudo code:**
```
function expression():
    check if the first input is a number. syntax error if its not.
    get the next token.
    if EOF is reached, return.
    call expression();
```
<br>



## Generating AST tree

Using the grammar, we can generate the AST tree for the input stream.

The structure and enums for AST are defined in the `def.h` file.

```c
// enum for AST
enum
{
    A_ADD,
    A_SUB,
    A_MUL,
    A_DIV,
    A_INTLIT
};

// AST structure
struct ASTnode
{
    // type of AST node
    int op;

    // child nodes
    struct ASTnode *left;
    struct ASTnode *right;

    // value, if any
    int intValue;
};
```
<br>

Each AST node may contain a left and / or a right child node, therefore capable of generating a tree like structure.

<br><hr>



For our case, we need a global Token that can be scanned any time. It is defined in the `data.h` file.

```c
extern_ struct Token token;
```
<br><hr>



The `ast.c` file contains function definitions for generating AST nodes of various types; mainly generic, unary and leaf nodes.

```c
// generic AST node generator
struct ASTnode *mkASTnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue)
{
    struct ASTnode *n;

    // dynamic memory allocation
    n = (struct ASTnode *)malloc(sizeof(struct ASTnode));

    // data entry
    n->op = op;

    n->left = left;
    n->right = right;

    n->intValue = intValue;

    return (n);
}



// AST leaf node generator function
struct ASTnode *mkASTLeafNode(int op, int intValue)
{
    struct ASTnode *n;
    n = mkASTnode(op, NULL, NULL, intValue);
    return (n);
}



// AST unary node generator function
struct ASTnode *mkASTUnaryNode(int op,  struct ASTnode *left)
{
    struct ASTnode *n;
    n = mkASTnode(op, left, NULL, 0);
    return (n);
}
```

<br><hr>

The `expr.c` file defines `primary()` function which always scans an INTLIT token. 

```c
static struct ASTnode *primary(void)
{
    struct ASTnode *n;

    if (token.token == T_INTLIT)
    {
        n = mkASTLeafNode(A_INTLIT, token.intValue);

        // scan next operation token
        scan(&token);
    }
    else
    {
        fprintf(stderr, "syntax error on line %d\n", line);
        exit(1);
    }

    return (n);
}
```

<br>

The main workflow of the parsing logic is as follows:

**Pseudo code:**
```
function generator():
    get a primary token.
    make an AST node.
    set its left child the primary token.
    get the next token. if it is EOF, return, else get the operation type and set it to the AST node.
    call the generator() function on the right child. The whole of the remaining input is treated as the right child here.
    return the generated tree.
```
<br>

The `ASTgen()` function parses the AST tree using the given logic. 

```c
struct ASTnode *ASTgen(void)
{
    struct ASTnode *n, *left, *right;

    left = primary();

    // end of file reached
    if (token.token == T_EOF)
    {
        return (left);
    }

    int op = ASTop(token.token);

    // scan next INTLINT
    scan(&token);

    right = ASTgen();

    n = mkASTnode(op, left, right, 0);

    return (n);
}
```
<br>



## Interpreting the AST tree

The interpreter interprets the AST tree with a simillar logic as used for parsing the tree.

**Pseudo Code:**
```
function interpret(node):
    if left child exists, call interpret() on the left child and store in leftVal.
    if right child exists, call interpret() on the right child and store in rightVal.

    if node is of type INTLIT, return its value.

    else according to the operation of the node, compute the operation with leftVal and rightVal, then return it.
```

The `interpret.c` file implements the `ASTinterpret()` function. It also prints the operations in the output stream while computing.

```c
// terminals to be printed to the output stream
char* ASTtok[] = {"+", "-", "*", "/"};
```

```c
int ASTinterpret(struct ASTnode *n)
{
    int left, right;

    // if left node, recursively get the value
    if (n->left)
    {
        left = ASTinterpret(n->left);
    }

    // if right node, recursively get the value
    if (n->right)
    {
        right = ASTinterpret(n->right);
    }

    if (n->op == A_INTLIT)
    {
        printf("INT \t%d\n", n->intValue);
    }
    else
    {
        printf("%d %s %d\n", left, ASTtok[n->op], right);
    }

    switch (n->op)
    {
    case A_ADD:
        return left + right;
    case A_SUB:
        return left - right;
    case A_MUL:
        return left * right;
    case A_DIV:
        return left / right;

    case A_INTLIT:
        return (n->intValue);
    
    default:
        fprintf(stderr, "unknown AST operation %d\n", n->op);
        exit(1);
    }
}
```
<br><hr>

## Testing

Input: `in01`

```
11  * 5 - 5 / 12 * 7
```
<br>

Output:

```
INT     11
INT     5
INT     5
INT     12
INT     7
12 * 7
5 / 84
5 - 0
11 * 5
result: 55
```

<br><hr>

input: `in02`

```
123 + 14
/ 123 - 1
+ 
```

Output:

```
syntax error on line 3
```
<br>

Successfully detected syntax error.

<br><hr>

input: `in03`

```
12 * 5 / 23

+  12
```

Output:

```
INT     12
INT     5
INT     23
INT     12
23 + 12
5 / 35
12 * 0
result: 0
```

<br><hr>

**Note:** At this point, the output is wrong, since there is no **operation precedence** present in our parser. The operators are simply computing in the reverse order of input stream **(in recursive call, base case returns first)**. In the next section, we will implement the operator precedence which will interpret the tree correctly according to precedence.

<br><hr>

Next chapter [operator precedence](/custom-c-compiler/operator%20precedence/readme.md)