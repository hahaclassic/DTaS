#!/bin/bash

if [[ ! (-e "./app.exe") ]]; then
    echo "Error! app.exe does not exist"
    exit 3
elif [[ ! -e "./func_tests/data" ]]; then
    echo "Error! The data folder does not exist"
    exit 1
fi


# checking positive tests
echo -e "\033[36mAll positive \033[0m"
failed=0

while IFS='' read -r line;
    do pos_files_out+=("$line");
done < <(find ./func_tests/data -name "pos_*_out.txt" | sort -k 1.7n)

while IFS='' read -r line;
    do pos_args+=("$line");
done < <(find ./func_tests/data -name "pos_*_args.txt" | sort -k 1.7n)

if [[ ! ${#pos_args[@]} -eq ${#pos_files_out[@]} ]]; then
    echo "Error! The number of positive in/out files is different"
    exit 2
fi 

for ((i=0; i<${#pos_args[@]}; i++))
do  
    (( count=i+1 ))
    if ./func_tests/scripts/pos_case.sh "${pos_args[$i]}" "${pos_files_out[$i]}"; then
        echo -e "Positive test $count\033[92m passed \033[0m"
    else
        echo -e "Positive test $count\033[91m failed \033[0m"
        failed+=1
    fi
done

# checking negative tests
echo ""
echo -e "\033[36mAll negative\033[0m"

while IFS='' read -r line;
    do neg_args+=("$line");
done < <(find ./func_tests/data -name "neg_*_args.txt" | sort -k 1.7n)

for ((i=0; i<${#neg_args[@]}; i++))
do  
    (( count=i+1 ))
    if ./func_tests/scripts/neg_case.sh "${neg_args[$i]}"; then
        echo -e "Negative test $count\033[92m passed \033[0m"
    else
        echo -e "Negative test $count\033[91m failed \033[0m"
        failed+=1
    fi
done

exit $failed
