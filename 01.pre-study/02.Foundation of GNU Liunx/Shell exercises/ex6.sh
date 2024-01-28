#!/bin/bash

#《鸟哥的私房菜》第十二章练习

if [ $# != 1 ]; then
	echo "Please enter one parameter."
elif [ "$1" != "hello" ]; then  	
	echo "Please enter \"hello\"."
else
	echo "Hello， how are you?"
fi
	
#exit 0
