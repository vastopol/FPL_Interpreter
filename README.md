# FP_Interpreter
A functional programming language based REPL for integer sequence manipulation.
The REPL is the interface to the memory management system and the interpreter. 
The REPL has primitive capabilities for automation of tasks through writing scripts.
The language is called `fpl`, which stands for FP Lite.
The REPL is called `fplr`, which stands for FP Lite REPL.
The file extention for script files is `.fpl`.

### For more information see:
* https://en.wikipedia.org/wiki/FP_(programming_language)
* http://www.math.bas.bg/bantchev/place/fp.html
* https://pdfs.semanticscholar.org/d4e1/218282009bed1f9c9011647d3029330082d8.pdf
* http://theory.stanford.edu/~aiken/publications/trs/RJ7100.pdf

### Installation
```
$ git clone https://github.com/vastopol/FP_Interpreter.git

$ cd FP_repl

$ make

$ bin/fplr
```

### Development Goals:
* Simple REPL: `fplr`
* Full Interpreter: (not started)

These goals explore:
Deveolpment and design of software, abstract syntax and paridigms of programming langauges, manipulation of data structures, 
recursive programming techinques, interpretation of code, etc...

### Syntax (primer)
The syntax and semantics of this interpreter is primarily FP language based, there is a also some inspiration from Lisp and Forth.
Some of the syntax has been changed, other features have been modified also for ease of use. 
For comprehensive docomentation of the syntax see "FP_repl/DOCS/syntax.dat".
This will show some of the more important basics of REPL interaction. 
such as...
(insert list here later)

### FP Dialects
FP was developed by John Backus as a notation in the late 1970's. It evolved into FL an IBM research language.
The language PLaSM is based on FL. Other examples and implementations exist also.
See: FP84, IFP, FurryPaws, ...