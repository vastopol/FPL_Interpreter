# FP_Interpreter
A functional programming language based REPL for integer sequence manipulation.
The REPL is the interface to the memory management system and the interpreter.
The REPL has primitive capabilities for simple automation of tasks through writing scripts.
The REPL is called `fplr`, which stands for: Functional Programming Language REPL.
The file extension for script files is `.fpl`.


### Dependencies
* g++11
* graphviz


### Installation
```
$ git clone https://github.com/vastopol/FP_Interpreter.git

$ make

$ bin/fplr
```

### Development Goals:
* Simple REPL: `fplr`
* Full Interpreter: (not started)

These goals explore:
Development and design of system level software, manipulation of complex data structures, recursive programming techniques, formal language theory, interpretation of code,
parser construction, etc...


### Syntax (primer)
The syntax and semantics of this interpreter are primarily derived from applicative functional languages and concatenation based stack languages.
Historically the main inspiration comes from: FP/FL, Lisp, Forth, Factor, Joy, J, PLaSM
Some of the syntax has been changed, other features have been modified also for ease of use.
For now this implementation is basically a small and limited subset of traditional FP/FL.
In later versions the syntax will most likely change and no longer be as compliant.
For comprehensive documentation of the syntax see "DOCS/syntax.dat".
This will show some of the more important basics of REPL interaction.
such as...
(insert list here later)


### For more information see:
#### FP
FP was developed by John Backus as a notation in the late 1970's. It evolved into FL an IBM research language.
The language PLaSM is based on FL. Other examples and implementations exist also.
See: FP84, IFP, FurryPaws, ...
* https://en.wikipedia.org/wiki/FP_(programming_language)
* http://www.math.bas.bg/bantchev/place/fp.html
* https://pdfs.semanticscholar.org/d4e1/218282009bed1f9c9011647d3029330082d8.pdf
* http://theory.stanford.edu/~aiken/publications/trs/RJ7100.pdf
