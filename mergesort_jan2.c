/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	// init
	struct argument *args = (struct argument *) arg;
	int l = args->left;
	int r = args->right;
	int level = args->level;
	int threshold; 
	pthread_t t1,t2;
	
	threshold = 5000;

	if (l >= r) {
		return NULL;
	}


	if (level >= threshold) {
		int mid = (l + r) / 2;
		

		struct argument * lArg = buildArgs(l, mid, level + 1);
		pthread_create(&t1, NULL, parallel_mergesort, lArg);

		struct argument * rArg = buildArgs(mid + 1, r, level + 1);
		pthread_create(&t2, NULL, parallel_mergesort, rArg);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);

		merge(l, mid, mid + 1, r);
	} else {
		my_mergesort(l, r);
	}

	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){

	struct argument *args = malloc(sizeof(struct argument));

	if (args == NULL) {
		perror("malloc failed");
		exit(1);
	}

	args->left = left;
	args->right = right;
	args->level = level;
		return args;
}

