#include <stdio.h>

void get_thread_task(int num_threads, int thread_id, int n) {
    // Calculate how many tasks each thread gets
    int base_chunk_size = n / num_threads;  // Minimum number of tasks per thread
    int remainder = n % num_threads;         // Extra tasks to be distributed among threads

    // Starting index for the current thread (distribute extra tasks round-robin)
    int start_index = thread_id * base_chunk_size + (thread_id < remainder ? thread_id : remainder);

    // Ending index for the current thread
    int end_index = start_index + base_chunk_size + (thread_id < remainder ? 1 : 0);

    // Output the task (indexes) assigned to this thread
    printf("Thread %d is assigned the following indexes: ", thread_id);
    for (int i = start_index; i < end_index; i++) {
        printf("%d ", i);
        // i will be the index you are starting with
    }
    printf("\n");
}

int main() {
    int n = 3;          // Length of the input string (e.g., 10 tasks)
    int num_threads = 4; // Total number of threads
    int thread_id = 3;   // ID of the current thread (this can be 0 to num_threads-1)

    // Call the function to determine the task (indexes) assigned to this thread
    get_thread_task(num_threads, thread_id, n);

    return 0;
}
