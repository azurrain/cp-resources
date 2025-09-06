#!/bin/bash

if [ $# -eq 0 ]; then
    return 1
fi

if [ ! -e $1 ]; then
    echo "文件不存在"
    return 1
fi

bsname=$(basename $1)
fnoext=$(basename $1 .cpp)
fullname=$(readlink -f $1)
suffix=${fullname##*.}
fileDirname=$(dirname $fullname)

if [ $suffix != "cpp" ]; then
    echo "不是 C++ 源文件"
    unset bsname
    unset fullname
    unset fileDirname
    unset suffix
    unset fnoext
    return 1
fi

program=$fileDirname/$fnoext.out
g++ -Wall -Wextra -Wconversion -DLOCAL -D_GLIBCXX_DEBUG -O2 -std=gnu++20 -fdiagnostics-color=always -I $(pwd) $fullname -o $program

if [ $? -eq 0 ]; then
    # echo -e "\033[36m\033[1m编译完成\033[0m"
    if [ $# -ge 2 ]; then
        i=0
        for input in $@; do
            if [ $i -eq 1 ]; then
                inputfullname=$(readlink -f $input)
                if [ -e $inputfullname ]; then
                    echo -e "\033[36m\033[1m$fnoext.out < $input\033[0m"
                    $program < $inputfullname
                else
                    echo -e "\033[36m\033[1m$input 不存在\033[0m"
                fi
            fi
            i=1
        done
        unset i
    else
        echo -e "\033[36m\033[1m$fnoext.out\033[0m"
        $program
    fi
    rm $program
else
    echo -e "\033[31m\033[1m编译失败\033[0m"
fi

unset bsname
unset fullname
unset fileDirname
unset suffix
unset program
unset fnoext
