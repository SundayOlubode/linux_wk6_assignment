#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_mode(double *arr, int size)
{
        int i, j, max_count = 0;
        double mode = arr[0];

        for (i = 0; i < size; i++)
        {
                int count = 0;
                for (j = 0; j < size; j++)
                {
                        if (arr[j] == arr[i])
                                count++;
                }
                if (count > max_count)
                {
                        max_count = count;
                        mode = arr[i];
                }
        }
        return mode;
}

double calculate_median(double *arr, int size)
{
        for (int i = 0; i < size - 1; i++)
        {
                for (int j = 0; j < size - i - 1; j++)
                {
                        if (arr[j] > arr[j + 1])
                        {
                                double temp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = temp;
                        }
                }
        }

        if (size % 2 == 0)
        {
                return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
        }
        else
        {
                return arr[size / 2];
        }
}

double calculate_std_dev(double *arr, int size)
{
        double sum = 0.0, mean;
        for (int i = 0; i < size; i++)
        {
                sum += arr[i];
        }
        mean = sum / size;

        double variance_sum = 0.0;
        for (int i = 0; i < size; i++)
        {
                variance_sum += pow(arr[i] - mean, 2);
        }

        return sqrt(variance_sum / size);
}