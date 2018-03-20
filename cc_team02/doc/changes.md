# Changes made to the Template

This file lists and justifies all changes made to the [mCc Template](https://github.com/W4RH4WK/mCc) not directly related to any of the assignments.

## Changes

- **cmake**: Also supporting `cmake` as build system because it provides better IDE-integration (and there should't be any conflict to meson).
- **ast.h**: This header acts as a "header-container" because the ast-components' definition is splitted to separate headers (for better modularization; according to their functionallity)
