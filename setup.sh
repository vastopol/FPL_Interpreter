#!/bin/bash

# script to build the FPL interpreter and manual
# this will create bin/ && manual.pdf in current directory

function main()
{
    build_interp
    build_manual
}

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

# build pdf manual from postscript
function build_manual()
{
    # code to pdf
    a2ps -R -1 code/main.cpp -o main.ps
    a2ps -R -1 code/header/* -o hed.ps
    a2ps -R -1 code/source/* -o src.ps
    ps2pdf main.ps main.pdf
    ps2pdf hed.ps  hed.pdf
    ps2pdf src.ps  src.pdf

    # documents to pdf (only the numbered ones matter)
    a2ps -R -1 docs/[0-9]* -o docs.ps
    ps2pdf docs.ps docs.pdf

    # join pdfs into manual
    pdfunite docs.pdf main.pdf hed.pdf src.pdf manual.pdf

    # cleanup extras
    rm *.ps docs.pdf main.pdf hed.pdf src.pdf
}

#----------------------------------------

# call script driver
main
