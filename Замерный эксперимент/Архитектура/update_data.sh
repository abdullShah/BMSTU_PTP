#!/bin/bash

COUNT=100

if [[ "$1" != "all" ]]; then
    if [ -n "$2" ]; then
        COUNT=$2
    fi

    filepath=$1 #external_index/size_10000
    size=$(echo "$filepath" | cut -d'_' -f2) #10000
    app="./apps/${filepath}.exe"

    for ((i=0; i<COUNT; i+=1)); do
        echo "$size" | "$app" >> ./data/"${filepath}".txt
    done
else
    if [ -n "$2" ]; then
        COUNT=$2
    fi

    dirapps=$(ls ./apps/)
    for dirapp in $dirapps; do #external_index
        mkdir -p "./data/${dirapp}/"
        method=$(echo "$dirapp" | cut -d'_' -f1)
        echo "${dirapp} first updating in progress"
        if [[ "$method" == "internal" ]]; then
            for app in $(ls ./apps/"$dirapp"/); do #size_1000.exe
                nameapp=$(basename "$app" .exe) #size_1000
                ./apps/"${dirapp}"/"${app}" >> ./data/"${dirapp}"/"${nameapp}".txt
            done
        else
            for app in $(ls ./apps/"$dirapp"/); do #size_1000.exe
                nameapp=$(basename "$app" .exe) #size_1000
                for ((i=0; i<COUNT; i+=1)); do
                    ./apps/"${dirapp}"/"${app}" >> ./data/"${dirapp}"/"${nameapp}".txt
                done
            done
        fi
        echo -e "${dirapp} first updating in done\n"
    done
fi
