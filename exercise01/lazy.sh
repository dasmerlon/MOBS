#!/bin/bash

mkdir lazycode
cd lazycode

cat << EOF > autocode.c
#include <stdio.h>
int main(void){
	printf("Hello, world!\n");
	return 0;
}
EOF

gcc -o autocode -Werror autocode.c

./autocode > greetings.txt
cat greetings.txt