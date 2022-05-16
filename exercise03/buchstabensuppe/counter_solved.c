#include "counting.h"

int alphabet[26];
char line[256];

void count_characters() {
	for (int i = 0; i < sizeof(line); i++) {
		if (line[i] == 0) {
			return;
		} else if (line[i] > 96 && line[i] < 123) {
			alphabet[line[i] - 97]++;
		} else if (line[i] > 64 && line[i] < 91) {
			alphabet[line[i] - 65]++;
		}
	}
}

void count(const char* input){
	FILE *file = fopen(input, "r"); /* should check the result */

	while (fgets(line, sizeof(line), file)) {
		/* note that fgets doesn't strip the terminating \n, checking its
		 presence would allow to handle lines longer that sizeof(line) */
		count_characters();
	}
	fclose(file);

}


