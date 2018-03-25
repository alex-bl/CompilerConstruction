# Assignment 2 -- Semantic Checks / Type Checking / IR

*due on 25 April 2018*

Now that we have obtained the AST of an input program we need to run additional checks to ensure it is semantically sane.
Not every input program accepted by the parser is actually a valid mC program.
The parser does not check types or other (semantic) properties.

In this assignment you have to implement the following checks:

- check for use of undeclared variable
- check for multiple declarations of the same variable in the same scope
- check for duplicated functions
- check for use of unknown functions
- check for presence of `main`
- check that all execution paths of non-void-functions return a value
- type checking

To implement these semantic checks, a data structure known as *symbol table* needs to be created.
This table is used while traversing the AST to check semantic properties.

## Task 1

- Find out what symbol tables are and how they are typically used.
- Implement the creation of symbol tables.

Each entry in the table should correspond to a variable in the input program.
Yet, what information goes into the symbol table and what doesn't is entirely up to you.
My recommendation is to have a dedicated struct for symbol table entries which can be modified easily.
Furthermore, I recommend having one symbol table per scope, which includes a pointer to the symbol table of the parent scope.

The symbol table is created by traversing the AST and handling each parameter, declaration, and use of variable.
Parameters and declarations result in new entries to the symbol table of the corresponding scope.
Contrary, a use of a variable triggers a lookup in the symbol table currently constructed.
The goal is to link each use of a variable to its corresponding entry in the symbol table.

Let me illustrate this by showing how to correctly model [*shadowing*](https://en.wikipedia.org/wiki/Variable_shadowing).
The two code snippets are semantically equivalent:

    {                         |         {
        int a;                |             int a0;
        int b;                |             int b0;
        a = 1;                |             a0 = 1;
        b = 2;                |             b0 = 2;
        {                     |             {
            int b;            |                 int b1;
            a = 3:            |                 a0 = 3:
            b = 4;            |                 b1 = 4;
            {                 |                 {
                a = 2;        |                     a0 = 2;
                              |
                int a;        |                     int a1;
                a = 1;        |                     a1 = 1;
            }                 |                 }
        }                     |             }
    }                         |         }

Here, each compound statement corresponds to a new scope.
Every time a new scope opens, a new (empty) symbol table is created.
`int a` results in a new entry stating that a variable of name `a` and type `int` has been declared.
Subsequent uses of `a` (eg `a = 1`), should be linked to this entry.

If the lookup fails for the current scope, a lookup in the parent scope is issued.
This happens recursively until the entry is found.
If no entry exists, you just found an undeclared variable and should report an error.

## Task 2

- Implement a check to detect uses of unknown functions.
- Implement a check which ensures there is one function named `main` present.
  It should not take any parameters and can return either `void` or `int`.
- Implement a check which ensures that every function has a unique name.
  Also take the builtin functions into account.

The top-level grammar rule of mC states that a `program` consists of 0 or more function definitions.
Therefore, by simply looking at the top most part of the AST you can easily see all functions defined.
Add to that the built-in functions stated by the specification and you have the set of all available functions.

Now, simply check each call expression, whether the target function is a member of this set.

## Task 3

- Implement a check which ensures that all execution paths of a function return a value, unless the function is declared to return `void`.

## Task 4

- Implement type checking.

As we do not have to worry about implicit type conversion or deal with type deduction, this should be rather simple.
This check should also cover call expressions: check for correct number and types of arguments as well as the return type.

## Task 5

- Implement the conversion from AST (including symbol tables) to [three-address code (TAC)](https://en.wikipedia.org/wiki/Three-address_code).
- Implement a way to output the generated TAC.

The checks from the previous tasks should ensure that your input program is actually valid.
We now leave the wonderful world of mCc's front-end and enter its core.

Pay attention that your TAC implementation should be independent from the AST implementation.
It should be possible to completely replace the front-end of the compiler without touching the core.

## Submission

Follow the steps stated in the first assignment, using the following command to build the archive and the link below.

    $ git archive --prefix=team_XX_assignment_2/ --format=zip HEAD > team_XX_assignment_2.zip

:email: [send email](mailto:alexander.hirsch@uibk.ac.at?subject=703602%20-%20Assignment%202)
