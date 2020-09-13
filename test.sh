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
test 1 "(1)"
test 8 "2*(1+3)"
test 5 "1+(2*4)-(2*2)"
test 2 "(2*(1+1)+2)/3"
test -3 "-5+2"
test 5 "1++4"
test 21 "(-10+3)*-3"
test -7 "-(3+4)"
test 12 "1+2, 4*3"
test 1 "a=1"
test 9 "num = 3, num * num"
test 10 "a = 5, b = 2, c = a * b"
test 2 "a = -3, a + 5"
test 12 "n = 2, ret = 3 * (n + 2)"
test 1 "1==1"
test 0 "1==2"
test 0 "1!=1"
test 1 "1!=0"
test 1 "0<1"
test 0 "1<1"
test 1 "1<=1"
test 0 "1<=0"
test 1 "1>=1"
test 0 "0>=1"
test 1 "num = 1, num = num + 1, num == 2"
test 0 "num"
test 10 "ret = 0, if(1) ret = 10, ret"
test 0 "ret = 0, if(0) ret = 10, ret"
test 10 "ret = 0, if(ret + 1 == 1) ret = 10 else ret = 5, ret"
test 5 "ret = 0, if(ret + 1 == 2) ret = 10 else ret = 5, ret"
test 2 "ret = 0, if(0) ret = 1 else if(1) ret = 2 else ret = 3, ret"
test 3 "ret = 0, if(0) ret = 1 else if(0) ret = 2 else ret = 3, ret"
test 11 "n = 0, while(n <= 10) n = n + 1, n"
test 4 "{ num = 3, num = num + 1, num }"
test 10 "a=0, b=0, while(a<5){ a=a+1, b=b+2 }, b"
test 8 "a=0, b=0, while(a<5){ a=a+1, if(b<8){ b=b+2 } }, b"
echo "OK"
