#include <pthread.h>	// pthreads
#include <stdio.h> 		// printf()
#include <unistd.h>		// sleep()

int shared_data[5]; //shared data structure accessed by multiple threads
pthread_mutex_t lock; // the mutex

void* thread_func1(void* arg);
void* thread_func2(void* arg);

int main(int argc, char* argv[]) {
	pthread_mutex_init(&lock, NULL); // initializes the mutex

	pthread_t t1, t2; // creates threads
	pthread_create(&t1, NULL, thread_func1, NULL);
	pthread_create(&t2, NULL, thread_func2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void* thread_func1(void* arg) {
	printf("thread_func1 waiting for lock\n");

	pthread_mutex_lock(&lock);  // acquires/waits for the lock
	printf("thread_func1 acquired lock\n");

	// modifies shared data
	shared_data[2] = shared_data[0] + shared_data[1];
	sleep(5);
	
	printf("thread_func1 releasing lock\n");
	pthread_mutex_unlock(&lock);  // releases the lock
	
	pthread_exit(NULL);
}

void* thread_func2(void* arg) {
	printf("thread_func2 waiting for lock\n");

	pthread_mutex_lock(&lock);  // acquires/waits for the lock
	printf("thread_func2 acquired lock\n");

	// modifies shared data
	shared_data[0] = shared_data[1] * shared_data[2];
	sleep(5);

	printf("thread_func2 releasing lock\n");
	pthread_mutex_unlock(&lock);  // releases the lock

	pthread_exit(NULL);
}