#include <stdio.h>
#include "guessing.h"

int binarySearch(int max, int min) {
	int num = (max + min) / 2;
	int x = evaluate(num);
	// printf("(%i, %i) \n", min, max);

	if (x == 0) {
		return num;

	} else if (x == 1) { 
		int min = num + 1;
		binarySearch(max, min);

	} else if (x == -1) { 
		int max = num - 1;
		binarySearch(max, min);
	}
}

int guess_the_number(){
	int max = 99999;
	int min = 0;
	int num = binarySearch(max, min);
	// printf("Number: %i \n", num);

	return num;
}