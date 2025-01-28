#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86gprintrin.h>
#include <math.h>

#define MAX_ITER 100000
#define MIN_ITER 1000

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

unsigned long long __rdtsc(void);

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

        unsigned long long t_start = __rdtsc();
        insertion_sort(arr, NMAX);
        unsigned long long t_end = __rdtsc();
        unsigned long long work_time = t_end - t_start;

        printf("%llu\n", work_time);
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
