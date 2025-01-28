#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <linux/time.h>

#ifndef NMAX
#error "Not find NMAX"
#endif

void insertion_sort(int *arr, size_t n)
{
    for (int *i = arr + 1; i < arr + n; i++)
    {
        int item = *i;
        int *j = i;
        while ((j > arr) && (item < *(j - 1)))
        {
            *j = *(j - 1);
            j--;
        }
        *j = item;
    }
}

extern int clock_gettime (clock_t __clock_id, struct timespec *__tp) __THROW;

int main(void)
{
    int arr[NMAX];

    srand(time(NULL));
    for (size_t i = 0; i < NMAX; i++)
        arr[i] = rand() % 7;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    insertion_sort(arr, NMAX);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    double work_time = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) / 1e6);
    printf("%.6lf\n", work_time);

    return 0;
}
