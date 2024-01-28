#!/bin/bash

#《鸟哥的私房菜》第十二章练习

declare -i fnum
declare -i lnum
declare -i mul


read -p "Please enter the first number: " fnum
read -p "Please enter the next  number: " lnum
	
mul=${fnum}*${lnum}

echo "${fnum} x ${lnum} = $mul"
	
exit 0
