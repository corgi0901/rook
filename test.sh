#!/bin/bash

test() {
    answer=$1
    input=$2

    result=`./rook "$input"`

    if [ "$answer" = "$result" ]; then
        echo "$input => $result"
    else
        echo "$input => $answer expected, but got $result"
        exit 1
    fi
}

test 42 "42"
test 0 "0"
test 9 "7+2"
test 4 "10-6"
test 8 "12 + 4 - 8"
test 10 "12 - 4 + 2"
test 8 "2 * 4"
test 3 "12 / 4"
test 10 "5 * 3 - 5"
test 9 "2 + 2 * 5 - 3"

echo "OK"