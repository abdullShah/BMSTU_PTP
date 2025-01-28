#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <linux/time.h>
#include <math.h>

#define MAX_ITER 100000
#define MIN_ITER 1000

#ifndef NMAX
#error "Not find NMAX"
#endif

void insertion_sort(int arr[], size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int item = arr[i];
        int j = i;
        while ((j > 0) && (item < arr[j - 1]))
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = item;
    }
}

extern int clock_gettime (clock_t __clock_id, struct timespec *__tp) __THROW;

int main(void)
{
    double datas[MAX_ITER];
    size_t q = 0;

    int arr[NMAX];
    int original_arr[NMAX];

    srand(time(NULL));
    for (size_t i = 0; i < NMAX; i++)
    {
        arr[i] = rand() % 7;
        original_arr[i] = arr[i];
    }

    double rse = 100.0;
    while (((rse > 1.0) || (q < MIN_ITER)) && (q < MAX_ITER))
    {
        for (size_t i = 0; i < NMAX; i++)
            arr[i] = original_arr[i];

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        insertion_sort(arr, NMAX);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        double work_time = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) / 1e6);
        printf("%.6lf\n", work_time);
        datas[q++] = work_time;

        double avg = 0.0;
        for (size_t i = 0; i < q; i++)
            avg += datas[i];
        avg /= q;

        double s_sq = 0.0;
        for (size_t i = 0; i < q; i++)
            s_sq += (datas[i] - avg) * (datas[i] - avg);

        if (q != 1)
        {
            s_sq /= (q - 1);
            double s = sqrt(s_sq);
            double std_err = s / sqrt(q);
            rse = std_err / avg * 100.0;
        }
    }

    return 0;
}
