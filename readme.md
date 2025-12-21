# Custom C compiler
A DIY compiler for a subset of the C language. 
<br><br>
This repository is based on the [ACWJ](https://github.com/DoctorWkt/acwj) repository by [DoctorWkt](https://github.com/DoctorWkt).

## Objective
- Building a self compiling compiler - a compiler for C, written in C.
- Target architecture: x86 - 64 & 32 bit systems.
- focus on implementation and practice over theory.

## Key components
**The main workflow of a compiler**

```

    [High level input]
            |
            V
    [Lexical analysis]  (tokenization) 
            |
            V
    [Syntactical analysis]  (grammar)
            |
            V
    [Semantics analysis]
            |
            V
    [Translation]  (code generation)
```

<br>

Therefore, the key components that will be implemented are as follows:
1. Parser / tokenizer
2. Lexer
3. Semantic analyzer
4. Translator

## Chapters
- [tokenization](./tokenization/readme.md)
- [parsing](./parsing/readme.md)
- [operator precedence](./operator%20precedence/readme.md)