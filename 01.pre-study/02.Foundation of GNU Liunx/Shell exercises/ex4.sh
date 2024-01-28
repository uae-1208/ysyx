#!/bin/bash

#《鸟哥的私房菜》第十二章练习

read -p "Please enter the filename: " filename

test ! -e $filename && echo "$filename does not exist" || (echo "$filename exists" && ls -l $filename)
	
#exit 0
