# Changes made to the Template

This file lists and justifies all changes made to the [mCc Template](https://github.com/W4RH4WK/mCc) not directly related to any of the assignments.

## Changes

The following changes were made.

#### CMake

This project also supports `cmake` as build-system because it provides better IDE-integration (until now). However `meson` is still the "default-build-system" because it requires less installation/configuration effort.

#### Additional modularization

The original template was "roughly splitted" into the following parts: **ast**, **ast\_visitor** and **ast\_print**.   
We tried to provide a more fine-grained modularization by "splitting" the functionality according to the **ast-element**: Each element now has its base implementation ([src/ast/basis](../src/ast/basis), respectively, [include/mCc/ast/basis](../include/mCc/ast/basis)), its visitor functionality  ([src/ast/visit](../src/ast/visit), respectively, [include/mCc/ast/visit](../include/mCc/ast/visit)) as well as printing functionality ([src/ast/print](../src/ast/print), respectively, [include/mCc/ast/print](../include/mCc/ast/print)).   
This modularization should provide a better separation of functionality as well as guarantee a concurrent implementation of the various aspects by minimizing possible intersections, respectively, merge conflicts.
