#!/bin/bash

# script to build the FPL interpreter and manual
# this will create bin/ && manual.pdf in current directory

#----------------------------------------

# build interpreter
function build_interp()
{
    cd code
    make
    mv bin ..
    make clean
    cd ..
}

# build manual from docs
function build_manual()
{
    a2ps -R -1 code/header/* -o hed.ps
    a2ps -R -1 code/source/* -o src.ps
    a2ps -R -1 code/main.cpp -o main.ps
    a2ps -R -1 DOCS/* -o docs.ps

    ps2pdf docs.ps docs.pdf
    ps2pdf main.ps main.pdf
    ps2pdf hed.ps  hed.pdf
    ps2pdf src.ps  src.pdf

    pdfunite docs.pdf main.pdf hed.pdf src.pdf manual.pdf

    rm *.ps docs.pdf main.pdf hed.pdf src.pdf
}

#----------------------------------------

build_interp
build_manual
