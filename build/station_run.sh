#!/bin/bash

function init {
    pad=$(printf '%.1s' "."{1..70})
	padlength=71

    make
    mkdir -p out

    valgrind --leak-check=full --error-exitcode=1 ./station_run
    valgrind_error=$?
}

function print_result {
	printf "%s" "$1"
	printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
	printf "%s\n" "$2"
}

function check_test {
    begin_test='out/output_'
    begin_result='ref/result_'
    termination='.out'

    arr=( "arrive_train" "leave_train" "add_train_car" "remove_train_cars" "move_train_cars" "find_express_train" "find_overload_train" "find_optimal_train" "find_heaviest_sequence_train" "order_train" "fix_overload_train" )

    for i in ${!arr[@]}
    do
        element=${arr[$i]}
        testFileName=$begin_test$element$termination
        resultFileName=$begin_result$element$termination
        result=$(diff $testFileName $resultFileName | wc -l)

        if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
            print_result "Test ${arr[$i]} " "passed"
        else
            print_result "Test ${arr[$i]} " "failed"
        fi
    done

    echo " "

    if [[ ${valgrind_error} -eq 0 ]]; then
        print_result "Valgrind errors " "passed"
    else
        print_result "Valgrind errors " "failed"
    fi

    echo " "
}

init
check_test
make clean_all &> /dev/null
