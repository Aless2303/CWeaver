# CWeaver | Simple C Compiler 

A basic C-like language compiler implementation using **Flex** and **Bison** to demonstrate compiler construction fundamentals.

## Overview

This project implements a simple compiler for a C-like language that supports basic programming constructs including variables, arithmetic expressions, control flow, and functions.

## Features

- **Data Types:** `int`, `float`, `double`, `void`
- **Operators:** Arithmetic (`+`, `-`, `*`, `/`) and comparison (`>`, `<`, `>=`, `<=`, `==`, `!=`)
- **Control Flow:** `if/else` statements and `while` loops
- **Functions:** Function declarations with parameters and return statements
- **I/O Operations:** `printf` and `scanf` support
- **Variables:** Declaration, assignment, and scoped symbol table
- **Comments:** Single-line (`//`) and multi-line (`/* */`)

## Tools Used

- **Flex** - Lexical analyzer generator for tokenizing input
- **Bison** - Parser generator for syntax analysis and grammar rules
- **C++** - Implementation language with STL containers for symbol management

## Key Implementation

### Files Structure
- `proiectulmeu.l` - Flex lexical analyzer specification
- `proiectulmeu.y` - Bison parser grammar and semantic actions
- Generated C files for compilation

### Core Components
- **Symbol Table:** Linked list-based variable storage with scope management
- **Function Management:** Dynamic function parsing and execution
- **Type System:** Support for multiple numeric types with unified representation
- **Scope Handling:** Stack-based scope management for blocks and functions

## Building

```bash
# Generate lexer and parser
flex proiectulmeu.l
bison -d proiectulmeu.y

# Compile
gcc -o compiler proiectulmeu.tab.c lex.yy.c -lfl
```

## Usage

```bash
./compiler < input_file.c
```

### Example Input
```c
int main() {
    int x = 10;
    if (x > 5) {
        printf("x is greater than 5");
    }
    return 0;
}
```

## Educational Purpose

This compiler demonstrates fundamental concepts in compiler construction:
- Lexical analysis with regular expressions
- Syntax analysis with context-free grammars
- Symbol table implementation
- Scope management
- Basic semantic analysis

**Note:** This is an educational project focused on frontend compiler techniques rather than a production compiler.
