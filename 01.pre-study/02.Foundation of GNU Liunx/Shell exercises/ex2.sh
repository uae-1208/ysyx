#!/bin/bash
# Program:
#	Program creates three files, which named by user's input and date command.
# History:
# 2015/07/16	VBird	First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

# 1. 讓使用者輸入檔案名稱，並取得 fileuser 這個變數；
echo -e "I will use 'touch' command to create 3 files." # 純粹顯示資訊
read -p "Please input your filename: " fileuser         # 提示使用者輸入

# 2. 為了避免使用者隨意按 Enter ，利用變數功能分析檔名是否有設定？
filename=${fileuser:-"filename"}           # 開始判斷有否設定檔名

# 3. 開始利用 date 指令來取得所需要的檔名了；
date1=$(date --date='2 days ago' +%Y%m%d)  # 前兩天的日期
date2=$(date --date='1 days ago' +%Y%m%d)  # 前一天的日期
date3=$(date +%Y%m%d)                      # 今天的日期
file1=${filename}${date1}                  # 底下三行在設定檔名
file2=${filename}${date2}
file3=${filename}${date3}

# 4. 將檔名建立吧！
touch "${file1}"                           # 底下三行在建立檔案
touch "${file2}"
touch "${file3}"

