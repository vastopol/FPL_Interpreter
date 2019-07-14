#!/bin/bash

# script to build the FPL interpreter and manual
# this will create bin/ && manual.pdf in current directory

# doesn't seem to work, copy paste into terminal
shopt -s expand_aliases
alias fpl='rlwrap bin/fplr'
alias build_fpl='./setup.sh -c && ./setup.sh && clear && rlwrap bin/fplr'

function main()
{

    if [ "$1" = "-c" ] ; then
        wiper
        exit 0
    fi

    build_manual
    build_interp
    tester
}

#----------------------------------------

# build interpreter
function build_interp()
{
    echo; echo "building interpreter"; echo
    cd code
    make debug
    mv bin ..
    make clean > /dev/null 2>&1
    cd ..
}

# build pdf manual from postscript
function build_manual()
{
    echo; echo "building manual"; echo
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
    rm *.ps docs.pdf main.pdf hed.pdf src.pdf > /dev/null 2>&1
}


function wiper()
{
    echo; echo "wiping"; echo
    rm -rf bin > /dev/null 2>&1

    rm -rf output* > /dev/null 2>&1

    rm manual.pdf > /dev/null 2>&1

    cd code
    make clean > /dev/null 2>&1

    cd ..
}


function tester()
{
    echo; echo "testing"; echo

    for file in $(ls user/tests) ; do
        echo $file; echo
        if ! bin/fplr "user/tests/$file" ; then # error info for segfaults
            dmesg | tail -1
        fi
        echo
    done
}

#----------------------------------------

# call script driver
main $@
