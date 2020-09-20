#!/bin/bash

test() {
    answer=$1
    input=$2
    testfile="test.rk"

    echo "$input" >> $testfile

    result=`./rook $testfile`

    if [ "$answer" = "$result" ]; then
        echo "$input => $result"
    else
        echo "$input => $answer expected, but got $result"
        exit 1
    fi

    rm $testfile
}

test 42 "func main(){ 42 }"
test 0 "func main(){ 0 }"
test 9 "func main(){ 7+2 }"
test 4 "func main(){ 10-6 }"
test 8 "func main(){ 12 + 4 - 8 }"
test 10 "func main(){ 12 - 4 + 2 }"
test 8 "func main(){ 2 * 4 }"
test 3 "func main(){ 12 / 4 }"
test 10 "func main(){ 5 * 3 - 5 }"
test 9 "func main(){ 2 + 2 * 5 - 3 }"
test 1 "func main(){ (1) }"
test 8 "func main(){ 2*(1+3) }"
test 5 "func main(){ 1+(2*4)-(2*2) }"
test 2 "func main(){ (2*(1+1)+2)/3 }"
test -3 "func main(){ -5+2 }"
test 5 "func main(){ 1++4 }"
test 21 "func main(){ (-10+3)*-3 }"
test -7 "func main(){ -(3+4) }"
test 12 "func main(){ 1+2, 4*3 }"
test 1 "func main(){ a=1 }"
test 9 "func main(){ num = 3, num * num }"
test 10 "func main(){ a = 5, b = 2, c = a * b }"
test 2 "func main(){ a = -3, a + 5 }"
test 12 "func main(){ n = 2, ret = 3 * (n + 2) }"
test 1 "func main(){ 1==1 }"
test 0 "func main(){ 1==2 }"
test 0 "func main(){ 1!=1 }"
test 1 "func main(){ 1!=0 }"
test 1 "func main(){ 0<1 }"
test 0 "func main(){ 1<1 }"
test 1 "func main(){ 1<=1 }"
test 0 "func main(){ 1<=0 }"
test 1 "func main(){ 1>=1 }"
test 0 "func main(){ 0>=1 }"
test 1 "func main(){ num = 1, num = num + 1, num == 2 }"
test 0 "func main(){ num }"
test 10 "func main(){ ret = 0, if(1) ret = 10, ret }"
test 0 "func main(){ ret = 0, if(0) ret = 10, ret }"
test 10 "func main(){ ret = 0, if(ret + 1 == 1) ret = 10 else ret = 5, ret }"
test 5 "func main(){ ret = 0, if(ret + 1 == 2) ret = 10 else ret = 5, ret }"
test 2 "func main(){ ret = 0, if(0) ret = 1 else if(1) ret = 2 else ret = 3, ret }"
test 3 "func main(){ ret = 0, if(0) ret = 1 else if(0) ret = 2 else ret = 3, ret }"
test 11 "func main(){ n = 0, while(n <= 10) n = n + 1, n }"
test 4 "func main(){ { num = 3, num = num + 1, num } }"
test 10 "func main(){ a=0, b=0, while(a<5){ a=a+1, b=b+2 }, b }"
test 8 "func main(){ a=0, b=0, while(a<5){ a=a+1, if(b<8){ b=b+2 } }, b }"
test 3 "func sum(a,b){a+b}, func main(){ sum(1,2) }"
test 12 "func sum(a,b){a+b}, func main(){ n=10, sum(n,2) }"
test 65 "func sum(a,b){a+b}, func main(){ n=10, sum(n, sum(n*5, 5)) }"
test 115 "func sum(a,b){a+b}, func mul(a,b){a*b}, func calc(a,b){sum(a,b) + mul(a,b) * 2}, func main(){ calc(5,10) }"
test 1 "func check(a){ ret, if(a>10) ret = 1 else ret = 0, ret }, func main(){ check(15) }"
test 55 "func fib(n){if(n<=2){return 1}else{return fib(n-1)+fib(n-2)}}, func main(){ret=fib(10)}"
echo "OK"
