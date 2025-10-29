#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "mergesort.h"

/* =========================================================
   Helper Functions: merge() & my_mergesort() (serial version)
   ========================================================= */

void merge(int leftstart, int leftend, int rightstart, int rightend) {
    int i = leftstart;
    int j = rightstart;
    int k = leftstart;

    /* Merge two sorted halves into temporary array B */
    while (i <= leftend && j <= rightend) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }

    /* Copy remaining elements */
    while (i <= leftend)  B[k++] = A[i++];
    while (j <= rightend) B[k++] = A[j++];

    /* Copy merged elements back to A */
    size_t count = (size_t)(rightend - leftstart + 1);
    memcpy(&A[leftstart], &B[leftstart], count * sizeof(int));
}

void my_mergesort(int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    my_mergesort(left, mid);
    my_mergesort(mid + 1, right);
    merge(left, mid, mid + 1, right);
}

/* =========================================================
   Parallel Merge Sort (pthread version)
   ========================================================= */

void *parallel_mergesort(void *arg_voidp) {
    struct argument *arg = (struct argument *)arg_voidp;
    int left  = arg->left;
    int right = arg->right;
    int level = arg->level;

    /* Base cases */
    if (left >= right) {
        free(arg);
        return NULL;
    }

    if (level >= cutoff) {
        my_mergesort(left, right);
        free(arg);
        return NULL;
    }

    int mid = left + (right - left) / 2;

    /* Create two child tasks (threads) */
    pthread_t tL, tR;
    struct argument *aL = buildArgs(left, mid, level + 1);
    struct argument *aR = buildArgs(mid + 1, right, level + 1);

    int rc1 = pthread_create(&tL, NULL, parallel_mergesort, (void *)aL);
    int rc2 = pthread_create(&tR, NULL, parallel_mergesort, (void *)aR);

    /* Handle left side */
    if (rc1 == 0) {
        pthread_join(tL, NULL);
    } else {
        /* If thread creation fails, do serial merge */
        my_mergesort(left, mid);
        free(aL);
    }

    /* Handle right side */
    if (rc2 == 0) {
        pthread_join(tR, NULL);
    } else {
        my_mergesort(mid + 1, right);
        free(aR);
    }

    /* Merge both halves after they are sorted */
    merge(left, mid, mid + 1, right);

    /* Free current thread's argument */
    free(arg);
    return NULL;
}

/* =========================================================
   Build Arguments (for pthread_create)
   ========================================================= */

struct argument *buildArgs(int left, int right, int level) {
    struct argument *a = (struct argument *)malloc(sizeof(struct argument));
    if (!a) {
        perror("malloc failed for struct argument");
        exit(EXIT_FAILURE);
    }
    a->left = left;
    a->right = right;
    a->level = level;
    return a;
}
