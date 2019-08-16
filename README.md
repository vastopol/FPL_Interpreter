# FPL_Interpreter

## Version 1.2

An interpreter for `fpl` an applicative functional programming language.
The language is structured on using functions to do integer and sequence manipulation.

The interpreter is called `fplr`, which stands for Functional Programming Language REPL.
The Read Evaluate Print Loop is the main user interface to the system.
The REPL has capabilities for simple automation of tasks through writing scripts.
The extension for script files is `.fpl`.

There are 3 main parts: memory management, parser, and evaluator.
There are 2 levels, the outer level handles the memory management and system tasks.
The inner level parses and evaluates the `fpl` statements.

## Dependencies
* make
* g++11
* graphviz
* a2ps
* ps2pdf
* pdfunite


## Installation
Following these steps will build the interpreter and the documentation manual.
```
$ git clone https://github.com/vastopol/FPL_Interpreter.git

$ cd FPL_Interpreter

$ ./setup.sh  # build

$ bin/fplr    # run
```

## Syntax
For comprehensive documentation of the syntax see section on syntax in the manual.
This section will show some of the more important basics of interaction.
The `fpl` language is built around the application of functions.
The function application operator is `:`
New functions can be created with function composition.
The function composition operator is `.`
A variable is either an integer or a sequence of integers.
Comments are with `#`

## Code Examples
Below are some basic examples of `fpl` code.

### Hello World
```
print Hello World

Hello World
```

### Factorial
```
def factorial = prod.intsto
factorial:5

120
```

### Sum of Squares
```
let l = <1,2,3,4,5,6,7,8,9,10>
def sum_squares = sum.map{square}
sum_squares:l

385
```

## Purpose and Goals
I started this project after reading some research papers written by John Backus.
I wanted to study functional programming and built a tool based on the FP/FL style notation.

These goals explore:
Development and design of system level software, programming language theory, parser construction, interpretation of code, etc...

## Misc Information:
For notes and more technical documentation see the manual.
