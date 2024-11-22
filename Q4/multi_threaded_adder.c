#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_THREADS 20

typedef struct
{
        int *array;
        int start;
        int end;
        long long subtotal;
} ThreadData;

long long grand_total = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_subset(void *arg)
{
        ThreadData *data = (ThreadData *)arg;
        long long local_subtotal = 0;

        for (int i = data->start; i < data->end; i++)
        {
                local_subtotal += data->array[i];
        }

        pthread_mutex_lock(&mutex);
        data->subtotal = local_subtotal;
        grand_total += local_subtotal;
        pthread_mutex_unlock(&mutex);

        return NULL;
}

void print_cpu_usage(struct rusage *start, struct rusage *end)
{
        long user_time = (end->ru_utime.tv_sec - start->ru_utime.tv_sec) * 1000000 + (end->ru_utime.tv_usec - start->ru_utime.tv_usec);
        long system_time = (end->ru_stime.tv_sec - start->ru_stime.tv_sec) * 1000000 + (end->ru_stime.tv_usec - start->ru_stime.tv_usec);

        printf("CPU Usage:\n");
        printf("User CPU Time: %ld microseconds\n", user_time);
        printf("System CPU Time: %ld microseconds\n", system_time);
        printf("Total CPU Time: %ld microseconds\n", user_time + system_time);
}

int main()
{
        int n, num_threads, elements_per_thread;
        int *numbers;
        pthread_t threads[MAX_THREADS];
        ThreadData thread_data[MAX_THREADS];
        struct rusage start, end;

        do
        {
                printf("Enter number of elements (200 < n <= 2000): ");
                scanf("%d", &n);
        } while (n <= 200 || n > 2000);

        num_threads = (n + 99) / 100;
        elements_per_thread = n / num_threads;

        numbers = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
                numbers[i] = i + 1;
        }

        getrusage(RUSAGE_SELF, &start);

        grand_total = 0;
        for (int i = 0; i < num_threads; i++)
        {
                thread_data[i].array = numbers;
                thread_data[i].start = i * elements_per_thread;
                thread_data[i].end = (i == num_threads - 1) ? n : (i + 1) * elements_per_thread;

                pthread_create(&threads[i], NULL, add_subset, &thread_data[i]);
        }

        for (int i = 0; i < num_threads; i++)
        {
                pthread_join(threads[i], NULL);
        }

        getrusage(RUSAGE_SELF, &end);

        printf("Number of elements: %d\n", n);
        printf("Number of threads: %d\n", num_threads);
        printf("Grand Total: %lld\n", grand_total);

        print_cpu_usage(&start, &end);

        free(numbers);
        pthread_mutex_destroy(&mutex);

        return 0;
}