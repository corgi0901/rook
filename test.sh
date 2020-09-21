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

test 42 "func main(){ put(42) }"
test 9 "func main(){ put(7+2) }"
test 4 "func main(){ put(10-6) }"
test 8 "func main(){ put(12 + 4 - 8) }"
test 8 "func main(){ put(2 * 4) }"
test 3 "func main(){ put(12 / 4) }"
test 10 "func main(){ put(5 * 3 - 5) }"
test 9 "func main(){ put(2 + 2 * 5 - 3) }"
test 1 "func main(){ put((1)) }"
test 8 "func main(){ put(2*(1+3)) }"
test 5 "func main(){ put(1+(2*4)-(2*2)) }"
test 2 "func main(){ put((2*(1+1)+2)/3) }"
test -3 "func main(){ put(-5+2) }"
test 5 "func main(){ put(1++4) }"
test 21 "func main(){ put((-10+3)*-3) }"
test -7 "func main(){ put(-(3+4)) }"
test 1 "func main(){ a=1, put(a) }"
test 9 "func main(){ num = 3, put(num * num) }"
test 10 "func main(){ a = 5, b = 2, c = a * b, put(c) }"
test 2 "func main(){ a = -3, put(a + 5) }"
test 12 "func main(){ n = 2, ret = 3 * (n + 2), put(ret) }"
test 1 "func main(){ put(1==1) }"
test 0 "func main(){ put(1==2) }"
test 0 "func main(){ put(1!=1) }"
test 1 "func main(){ put(1!=0) }"
test 1 "func main(){ put(0<1) }"
test 0 "func main(){ put(1<1) }"
test 1 "func main(){ put(1<=1) }"
test 0 "func main(){ put(1<=0) }"
test 1 "func main(){ put(1>=1) }"
test 0 "func main(){ put(0>=1) }"
test 1 "func main(){ num = 1, num = num + 1, put(num == 2) }"
test 0 "func main(){ put(num) }"
test 10 "func main(){ ret = 0, if(1) ret = 10, put(ret) }"
test 0 "func main(){ ret = 0, if(0) ret = 10, put(ret) }"
test 10 "func main(){ ret = 0, if(ret + 1 == 1) ret = 10 else ret = 5, put(ret) }"
test 5 "func main(){ ret = 0, if(ret + 1 == 2) ret = 10 else ret = 5, put(ret) }"
test 2 "func main(){ ret = 0, if(0) ret = 1 else if(1) ret = 2 else ret = 3, put(ret) }"
test 3 "func main(){ ret = 0, if(0) ret = 1 else if(0) ret = 2 else ret = 3, put(ret) }"
test 11 "func main(){ n = 0, while(n <= 10) n = n + 1, put(n) }"
test 4 "func main(){ { num = 3, num = num + 1, put(num) } }"
test 10 "func main(){ a=0, b=0, while(a<5){ a=a+1, b=b+2 }, put(b) }"
test 8 "func main(){ a=0, b=0, while(a<5){ a=a+1, if(b<8){ b=b+2 } }, put(b) }"
test 3 "func sum(a,b){a+b}, func main(){ ret=sum(1,2), put(ret) }"
test 12 "func sum(a,b){a+b}, func main(){ n=10, ret=sum(n,2), put(ret) }"
test 65 "func sum(a,b){a+b}, func main(){ n=10, ret=sum(n, sum(n*5, 5)), put(ret) }"
test 115 "func sum(a,b){a+b}, func mul(a,b){a*b}, func calc(a,b){sum(a,b) + mul(a,b) * 2}, func main(){ ret=calc(5,10), put(ret) }"
test 1 "func check(a){ ret, if(a>10) ret = 1 else ret = 0, ret }, func main(){ ret=check(15), put(ret) }"
test 55 "func fib(n){if(n<=2){return 1}else{return fib(n-1)+fib(n-2)}}, func main(){ ret=fib(10), put(ret) }"
echo "OK"
