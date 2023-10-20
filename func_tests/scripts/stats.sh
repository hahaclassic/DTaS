#!/bin/bash

percentage()
{
    (( success=$2*100/$1 ))
    if [[ success -eq 100 ]]; then
        echo -e "\033[92m$success%\033[0m"
    else
        echo -e "\033[91m$success%\033[0m"
    fi
}

touch ./out/result
./func_tests/scripts/func_tests.sh | tee ./out/result

pos_all=$(grep -c "Positive" ./out/result)
neg_all=$(grep -c "Negative" ./out/result)

pos_passed=0
neg_passed=0
while IFS= read -r line; do
    k=0
    for word in $line; do
        if [[ $word =~ "Positive" ]]; then
            k=1
        elif [[ $word =~ "passed"  && $k -eq 1 ]]; then
            (( pos_passed++ ))
        elif [[ $word =~ "Negative" ]]; then
            k=2
        elif [[ $word =~ "passed"  && $k -eq 2 ]]; then
            (( neg_passed++ ))
        fi
    done
done < ./out/result

echo ""
# Percentage of completed tests
if [[ $pos_all -eq 0 ]]; then
    echo "There are no positive tests"
else
    p=$(percentage "$pos_all" "$pos_passed")
    echo "$p of positive tests passed"
fi

# Percentage of completed tests
if [[ $neg_all -eq 0 ]]; then
    echo "There are no negative tests"
else
    p=$(percentage "$neg_all" "$neg_passed")
    echo "$p of negative tests passed"
fi

(( failed=neg_all+pos_all-neg_passed-pos_passed ))
exit "$failed"
