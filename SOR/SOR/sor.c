#include "sor.h"
#include <stdlib.h>
#include<stdio.h>
#pragma warning(disable:6386)
static int power(int a, int n) {
    int b = 1;
    for (int i = 0;i < n;i++) {
        b *= a;
    }
    return b;
}
static void _shell_sort_1(int* array, int size) {
    for (int s = size; s > 0; s /= 2) {
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
    }
}
static void _shell_sort_2(int* array, int size) {
    for (int s = size; s > 0; s = 5 * s / 11) {
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
    }
}
int* counter_3(int n, int* size) {
    int* arr = (int*)(malloc)(4 * sizeof(int));
    int* arr1;
    int s = 0;
    int i = 1;
    int p = 0;
    if (arr) {
        arr[0] = 1;
        do {
            arr[i] = (arr[i - 1] + 1) * 2 - 1;
            arr1 = realloc(arr, sizeof(int) * ((long long)i + 2));
            if (arr1 != NULL) {
                arr = arr1;
            }
            p = arr[i];
            i++;
            *size = i;
        } while (p < n);
    }
    return arr;
}
static void _shell_sort_3(int* array, int size) {
    int n = 0;
    int* count = counter_3(size, &n);
    int s;
    while (n > 0) {
        s = count[n - 1];
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
        n--;
    }
    free(count);
}
static int* counter_4(int n, int* size) {
    int* arr = (int*)(malloc)(3 * sizeof(int));
    int* arr1;
    int s = 0;
    int i = 1;
    int p = 0;
    if (arr) {
        arr[0] = 1;
        do {
            arr1 = realloc(arr, sizeof(int) * ((long long)i + 2));
            if (arr1 != NULL) {
                arr = arr1;
            }
            arr[i] = power(4, i) + 3 * power(2, i - 1) + 1;
            p = arr[i];
            i++;
            *size = i;
        } while (p < n);
    }
    return arr;
}
static void _shell_sort_4(int* array, int size) {
    int n = 0;
    int* count = counter_4(size, &n);
    int s;
    while (n > 0) {
        s = count[n - 1];
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
        n--;
    }
    free(count);
}
static int* pratta(int n, int* count) {
    int* arr = malloc(5 * sizeof(int));
    int* arr1;
    int size = 1;
    int size0 = 0;
    int size00;
    int p = 0;
    int i = 1;
    int k = 0, s = 2;
    if (arr) {
        arr[0] = 1;
        do {
            size00 = size0;
            size0 = size;
            size = size + power(2, i);
            *count = size;
            if (size > 0) {
                arr1 = realloc(arr, sizeof(int) * size);
                if (arr1 != NULL) {
                    arr = arr1;
                }
            }
            for (int j = size0;j < size;j += 2) {
                arr[j] = arr[size00 + p] * 2;
                k = arr[size00 + p] * 3;
                p++;
                *count = j + 1;
                if (k >= n) {
                    return arr;
                }
                arr[j + 1] = k;
                s = j + 1;
            }
            p = 0;
            i++;
        } while (i < n);
    }
    return arr;
}


static int counter_5(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                for (int k = j; k < size - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                size -= 1;
                if (arr[i] == arr[j]) {
                    j--;
                }
            }
        }
    }
    for (int s = size; s > 0; s /= 2) {
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (arr[i] > arr[j]) {
                    int temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
    }
    return size;
}
static void _shell_sort_5(int* array, int size) {
    int n = 0;
    int* count = pratta(size, &n);
    int newsize = counter_5(count, n);
    n = newsize;
    int s;
    while (n > 0) {
        s = count[n - 1];
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
        n--;
    }
    free(count);
}
static int* counter_6(int n, int* size) {
    int* arr = malloc(10 * sizeof(int));
    int* arr1;
    int i = 8;
    int p = 0;
    int k = 1;
    if (arr) {
        arr[0] = 1;
        arr[1] = 4;
        arr[2] = 10;
        arr[3] = 23;
        arr[4] = 57;
        arr[5] = 132;
        arr[6] = 301;
        arr[7] = 701;
        do {
            arr1 = realloc(arr, sizeof(int) * ((long long)i + 2));
            if (arr1 != NULL) {
                arr = arr1;
            }
            arr[i] = (int)(arr[i-1] * 2.25);
            k = arr[i];
            i++;
            *size = i;
        } while (k < n);
    }
    return arr;
}
static void _shell_sort_6(int* array, int size) {
    int n = 0;
    int* count = counter_6(size, &n);
    int s;
    while (n > 0) {
        s = count[n - 1];
        for (int i = 0; i < size; i++) {
            for (int j = i + s; j < size; j += s) {
                if (array[i] > array[j]) {
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                }
            }
        }
        n--;
    }
    free(count);
}
static sort_info_t s_sortList[] =
{
{ _shell_sort_1,SORT_SHELL,SORT_SUBQUADRATIC,"delta(k)=delta(k-1)/2" },
{ _shell_sort_2,SORT_SHELL,SORT_SUBQUADRATIC,"delta(k)=delta(k-1)*5/11" },
{ _shell_sort_3,SORT_SHELL,SORT_SUBQUADRATIC,"delta(k)={2^n-1} n>0" },
{ _shell_sort_4,SORT_SHELL,SORT_SUBQUADRATIC,"delta(k)={4^n+3*2^(n-1)+1,1} n>0" },
{ _shell_sort_5,SORT_SHELL,SORT_SUBQUADRATIC,"delta(k)={2^n*3^m}n,m>0"},
{ _shell_sort_6,SORT_SHELL,SORT_SUBQUADRATIC,"empirical,delta(k-1)=delta(k)*2.25" },
};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
    *count = sizeof(s_sortList) / sizeof(s_sortList[0]);
    return s_sortList;
}
