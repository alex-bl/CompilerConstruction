# mC Specification

This document defines *mC* -- a tiny, C-like language used throughout this pro-seminar.
The semantics of mC are identical to C unless otherwise specified.

## Grammar

The next segment presents the grammar of mC using this notation:

- `#` starts a line comment
- `,` indicates concatenation
- `|` indicates alternation
- `( )` indicates grouping
- `[ ]` indicates optional parts (0 or 1)
- `{ }` indicates repetition (1 or more)
- `[ ]` and `{ }` can be combined to represent *0 or more repetition*
- `" "` indicates a terminal string
- `/ /` indicates a [RegEx]

[RegEx]: <https://www.regular-expressions.info/>

```
# Primitives

alpha            = /[a-zA-Z_]/

alpha_num        = /[a-zA-Z0-9_]/

digit            = /[0-9]/

identifier       = alpha , [ { alpha_num } ]

bool_literal     = "true" | "false"

int_literal      = [ "-" ] , { digit }

float_literal    = [ "-" ] , { digit } , "." , { digit }

string_literal   = /"[^"]*"/

# Operators

unary_op         = "-" | "!"

binary_op        = "+"  | "-" | "*" | "/"
                 | "==" | "!="
                 | "<"  | ">" | "<=" | ">="


# Types

type             = "bool" | "int" | "float" | "string"


# Declaration / Assignment

declaration      = type , identifier

assignment       = identifier , "=" , expression


# Expressions

expression       = single_expr , [ binary_op , expression ]

single_expr      = literal
                 | identifier
                 | call_expr
                 | unary_op , expression
                 | "(" , expression , ")"

literal          = bool_literal
                 | int_literal
                 | float_literal
		 | string_literal


# Statements

statement        = if_stmt
                 | while_stmt
                 | ret_stmt
                 | declaration , ";"
                 | assignment  , ";"
                 | expression  , ";"
                 | compound_stmt

if_stmt          = "if" , "(" , expression , ")" , statement , [ "else" , statement ]

while_stmt       = "while" , "(" , expression , ")" , statement

ret_stmt         = "return" , [ expression ] , ";"

compound_stmt    = "{" , [ { statement } ] , "}"


# Function Definition / Call

function_def     = ( "void" | type ) , identifier , "(" , [ parameters ] , ")" , compound_stmt

parameters       = declaration , [ { "," , declaration } ]

call_expr        = identifier , "(" , [ arguments ] , ")"

arguments        = expression , [ { "," expression } ]


# Program

program = [ { function_def } ]
```

## Comments

mC supports only *C-style* comments, starting with `/*` and ending with `*/`.
Like in C, they can span across multiple lines.
Comments are discarded by the parser, but do not forget to take newlines into account.

## Special Semantics

### Boolean

For mC we consider `bool` a first-class citizen, distinct from `int`.
Yet we skip boolean binary operators like `&&` and `||`.

### Strings

Strings are immutable and do not support any operation (eg concatenation).
Yet, like comments, strings can span across multiple lines.

Their sole purpose is to be used with a `print` function for which an implementation will be provided by the compiler.

### Type Conversion

There are no type conversion, neither implicit nor explicit.

An expression used as a condition (`if` or `while`) is expected to be of type `bool`.
This will be enforced later on by the type checker.

### Program

Your top-level rule is `program` which simply consists of a 0 or more function definitions.
While the parser happily accepts empty source files, we will later enforce that one function named `main` must be present.
This is the entry point of the program.

### Declaration, Definition, and Initialization

`declaration` is used to declare variables which can then be initialised with `assignment`.

Furthermore we do not provide a way to declare functions.
All functions are declared by their definition.
It is possible to use a function before it has been defined.

### Empty Parameter List

In C, the parameters list of a function taking no arguments contains only `void`.
For mC we simply use an empty parameter list.
Hence, instead of writing `int foo(void)` we write `int foo()`, where `foo` is the name of a function returning an `int` and taking no arguments.

## I/O

The following built-in functions will be provided by the compiler for I/O operations:

- `print`       outputs a given string to `stdout`
- `print_nl`    outputs the new-line character (`\n`) to `stdout`
- `print_int`   outputs a given integer to `stdout`
- `print_float` outputs a given float to `stdout`
- `read_int`    reads an integer from `stdin`
- `read_float`  reads a float from `stdin`

With these, it we can create simple, interactive programs.
