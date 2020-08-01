#!/bin/bash

test() {
    answer=$1
    input=$2

    result=`./rook $input`

    if [ "$answer" = "$result" ]; then
        echo "$input => $result"
    else
        echo "$input => $answer expected, but got $result"
        exit 1
    fi
}

test 42 "42"
test 0 "0"

echo "OK"