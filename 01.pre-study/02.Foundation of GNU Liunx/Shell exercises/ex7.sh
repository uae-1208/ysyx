#!/bin/bash

#《鸟哥的私房菜》第十二章练习

read -p "Please enter \"one\" or \"two\" \"three\": " num
	
case $num in
	"one")
		echo "one!"	
		;;
	"two")
		echo "two!"
		;;	
	"three")
		echo "three!"
		;;
	*)
		echo "Please enter \"one\" or \"two\" \"three\"!" 
		;;
esac

#exit 0
