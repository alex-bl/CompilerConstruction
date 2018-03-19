# CC team02

See [here](README_original.md) for the original README

## Content

- cc_team02 using cmake
- template provided from https://github.com/W4RH4WK/mCc setup with cmake

## Internal notes

This section contains internal notes about the given template.

#### src/ast.c
Contains "structs for ast": Every ast-node is a struct containing holding various information. Its structs are used within **parser.y**.  
**Existing within template**:

- expression_literal
- expression\_binary\_op
- expression_parenth
- int-literal
- float-literal

- binary operators
- expression

**Missing**:

- comments (discarded, but remember newlines)
- literals:
	- bool literals
	- string literals
- arrays
- operators:
	- unary
- declaration
- assignment
- statements:
	- if
	- while
	- return
	- compound
- functions:
	- definition
	- parameters
	- function-call
- program

----------------

#### src/ast_visit.c
Contains infrastructure to traverse the ast. It defines "interfaces" (e.g. callback-based functions): This is used in combination with **ast_visit.c** (see next).  
**Existing within template:**  

- visit\_expression
- visit\_literal

**Missing**:

----------------

#### src/ast_print.c
Contains functions to "draw" a dot-graph. Its functions are called inside the **ast_visit.c**.  
**Existing within template**:  

- dot_begin
- dot_end
- dot_node
- dot_edge
- dot\_expression\_literal
- dot\_expression\_binary_op
- dot\_expression\_parenth
- dot_literal
- dot\_literal\_float

**Missing**:

----------------