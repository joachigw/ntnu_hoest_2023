#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];

void *go (void *n) {
	printf("Hello from thread %ld\n", (long) n);
	phtread_exit(100 + n);
}

int main() {
	long i;
	for (i = 0; i < NTHREADS; i++) phtread_create(&threads[i], NULL, go, (void*) i);
	for (i = 0; i < NTHREADS; i++) {
		long exitValue;
		phtread_join(threads[i], (void*) &exitValue);
		printf("Thread %ld returned with %ld\n", i, exitValue);
	}
	printf("Main thread done.\n");
	return 0;
}
