#include "counting.h" //nicht aendern!
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int alphabet[26]; // nicht aendern!


typedef struct params {
    char *buffer;
	long start_index;
	long end_index;
	int *sub_alphabet; // each thread gets its own alphabet array
} params;


void *char_counter(void *args) {
	params *input = (params*) args;
	long start = input->start_index;
	long end = input->end_index;
	int *sub = input->sub_alphabet;

	// Go through the file from the given start to the given end
	for (int i = start; i < end; i++) {
		char character = input->buffer[i];

		// If the character is between A-Z (ASCII-value: 65-90) 
		// increment the number at the correct index.
		// (e.g. A=65 -> sub[65-65] = sub[0])
		if (character >= 65 && character <= 90) {
			sub[character-65] += 1;
		// Do the same for a-z (ASCII-value: 97-122)
		} else if (character >= 97 && character <= 122) {
			sub[character-97] += 1;
		}
	}

	free(args);
	return EXIT_SUCCESS;
}


void count(const char *input) { // Dateiname als Input
	// set the number of threads
	long threads = 16;
	pthread_t tids[threads];
	int alphabets[threads * 26];
	
	// Reset the alphabets arrays for the threads
	for (int i = 0; i < (26 * threads); i++) {
		alphabets[i] = 0;
	}

	FILE *fileptr;
	char *buffer;
	long filelen;

	fileptr = fopen(input, "rb"); // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);  // Jump to the end of the file
	filelen = ftell(fileptr);     // Get the current byte offset in the file
	rewind(fileptr);              // Jump back to the beginning of the file

	buffer = (char *)malloc(filelen * sizeof(char)); // Reserve enough memory for the file
	fread(buffer, filelen, 1, fileptr);  // Read in the entire file
	
	// Set the file length for a single thread by dividing the file by the number of threads
	long buffer_len = filelen / threads;
	long start_index = 0;

	// Create the threads
	for (int i = 0; i < threads; i++) {
		params *args = malloc(sizeof(params));
		args->buffer = buffer;
		args->start_index = start_index;
		
		// Set the end index for a thread to the start index + divided file length.
		// For the last thread, set the end index to the original end of the file
		// in case some characters are missing due to odd splitting.
		if (i == (threads-1)) {
			args->end_index = filelen;
		} else {
			args->end_index = start_index + buffer_len;
		}
		args->sub_alphabet = &alphabets[i * 26];
		//printf("Thread: %d, start: %ld, end: %ld\n", i, start_index, args->end_index);
		pthread_create(&tids[i], NULL, &char_counter, (void*) args);

		// The next thread starts at the end of the previous thread
		start_index = start_index + buffer_len;
	}
	
	// Combine the counted characters to the alphabet array.
	for (int i = 0; i < threads; i++) {
        pthread_join(tids[i], NULL);  
		for (int j = 0; j < 26; j++) {
			//printf("Thread: %d, Char: %d, Left: %d, Right: %d\n", 
			//    i, j,
			//	alphabet[j], alphabets[i][j]
			//);
			alphabet[j] += alphabets[i * 26 + j];
		}
    }

	fclose(fileptr);  // Close the file
}




/*
// Alternative Solution:
// - create a thread for each character (a-z)
// - each thread goes through the whole file and counts its corresponding character


typedef struct params {
    char *buffer;
	long filelen;
    int offset;
} params;


void *char_counter(void *args) {
	params *input = (params*) args;
	int offset = input->offset;
	int counter = 0;
	for (int i = 0; i < input->filelen; i++) {
		char character = input->buffer[i];
		
		if (character == offset+65 || character == offset+97) {
			counter++;
		}
	}
	alphabet[offset] = counter;
	free(args);

	return EXIT_SUCCESS;
}


void count(const char *input) { // Dateiname als Input
	pthread_t tids[26];
	
	FILE *fileptr;
	char *buffer;
	long filelen;

	fileptr = fopen(input, "rb"); // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);  // Jump to the end of the file
	filelen = ftell(fileptr); // Get the current byte offset in the file
	rewind(fileptr);          // Jump back to the beginning of the file

	buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
	fread(buffer, filelen, 1, fileptr);              // Read in the entire file
	
	for (int offset = 0; offset < 26; offset++) {
		params *args = malloc(sizeof(params));
		args->buffer = buffer;
		args->filelen = filelen;
		args->offset = offset;
		int success = pthread_create(&tids[offset], NULL, &char_counter, (void*) args);
	}
	
	for (int offset = 0; offset < 26; offset++) {
        pthread_join(tids[offset], NULL);  
    }

	fclose(fileptr);                                 // Close the file
}
*/