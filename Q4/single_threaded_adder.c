#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

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
        int n;
        long long total = 0;
        struct rusage start, end;

        do
        {
                printf("Enter number of elements (200 < n <= 2000): ");
                scanf("%d", &n);
        } while (n <= 200 || n > 2000);

        int *numbers = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
                numbers[i] = i + 1;
        }

        getrusage(RUSAGE_SELF, &start);

        for (int i = 0; i < n; i++)
        {
                total += numbers[i];
        }

        getrusage(RUSAGE_SELF, &end);

        printf("Number of elements: %d\n", n);
        printf("Total: %lld\n", total);

        print_cpu_usage(&start, &end);

        free(numbers);

        return 0;
}