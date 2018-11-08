#!/bin/bash

# script to make and setup the fpl repl
# run this to install the bin folder in current directory

set -e

cd code
make
mv bin ..
