# Pseudoku

A pseudoku solver written in C.

## Configuration

Two parameters `BASE` and `LEADING_ZERO` can be configured in header file `config.h`.

- `BASE` refers to the base of the pseudoku puzzle. Default is `10`. Any value between `1` and `32` is legitimate.

- `LEADING_ZERO` indicates whether the pseudoku puzzle allows the leading digit to be 0. It defaults to `0`, which disables the leading zero.

Recompile after altering `config.h`.

## Compilation

Execute `gcc main.c -o main`.

## Sidenote

'Pseudoku' is a coined portmanteau of 'Pseudo' and 'Sudoku'. The game presents a puzzle in the form of column addition, where each symbol represents a distinct digit. 

The notion to write this solver stems from a failed attempt to solve a billboard puzzle for the International Day of Mathematics by hand. Simpler versions of such puzzles can also be seen in junior mathematical competitions.

The program contains much minor optimization, which is indeed unnecessary in such a simple program. They are mostly for demonstration purposes.
