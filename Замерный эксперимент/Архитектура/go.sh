#!/bin/bash

MAX_ITER=100000
MIN_ITER=1000

COUNT=100

echo "build apps is creating"
bash ./build_apps.sh
echo -e "creating is done\n"

bash ./update_data.sh "all" $COUNT

dirs=$(ls ./data/)
for dir in $dirs; do #external_index
    files=$(ls ./data/"$dir"/)
    method=$(echo "$dir" | cut -d'_' -f1)
    if [[ "$method" != "internal" ]]; then
        echo "${dir} is updating"
        for file in $files; do
            echo "${file} is updating" #size_1000.txt
            n=$(basename "$file" | cut -d'_' -f2 | cut -d'.' -f1) #1000
            rse=$(echo "./data/$dir/$file" | python3 get_rse.py)
            cnt=$COUNT
            while (( ($(echo "$rse > 1" | bc -l) || cnt < MIN_ITER) && cnt < MAX_ITER)); do
                bash ./update_data.sh "${dir}/size_${n}" $COUNT
                cnt=$((cnt+COUNT))
                rse=$(echo "./data/$dir/$file" | python3 get_rse.py)
                #echo $rse
                #echo $cnt
            done
            echo -e "updating is done\n"
        done
    fi
done

echo "datas is preprocessing"
python3 make_preproc.py
echo -e "preprocessing is done\n"

echo "datas is postprocessing"
python3 make_postproc.py
echo -e "postprocessing is done\n"
