#!/bin/bash


# ----------------------------------
# Colors
# ----------------------------------
NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'
DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
YELLOW='\033[1;33m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
WHITE='\033[1;37m'

CUB3D='./cub3D'

if [ $# -ne 1 ]; then
	echo "missing argument"
	exit 1
	fi

path=$@

if ! [[ "$path" =~ ^("good"|"bad")$ ]]; then
	echo "invalid path: $path right value: ["good","bad"]"
	exit 1
	fi

for file in maps/"$path"/*; 
do
	echo -e "testing : ${BLUE}$file${NOCOLOR}"
	output=$("$CUB3D" "$file" 2>&1)
	if [ $? -ne 0 ]; then
		echo -e "${GREEN}[OK] $file failed as expected${NOCOLOR}"
		echo -e "Output: \n${GREEN}$output${NOCOLOR}"
	else
		echo -e "${RED}[KO] $file should fail${NOCOLOR}"
		echo -e "Output: \n${RED}$output${NOCOLOR}"
	fi
	valgrind --leak-check=full --error-exitcode=42 "$CUB3D" "$file" 2> /dev/null
	if [ $? -eq 42 ]; then
		echo -e "${RED}[LEAK]${NOCOLOR} $file"
	else
		echo -e "${GREEN}[NO LEAK]${NOCOLOR} $file"
	fi
	echo
done
exit 0