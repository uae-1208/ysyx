#!/bin/bash

#《鸟哥的私房菜》第十二章练习

echo "The file name is $0."
echo "There are $# parameters."
test $# -lt 2 && echo "The number of parameters is less than 2"
echo "The parameters are: $@."
echo "The first parameter is $1."

#exit 0
