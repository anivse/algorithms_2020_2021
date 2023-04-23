#include <stdio.h>
#define N 9
#include <locale.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
void Fill(int arr[], int size) {
	for (int i = 0;i < size;i++) {
		arr[i] = i + 1;
	}
}
void Print(int  const arr[], int size) {
	for (int i = 0;i < size;i++) {
		printf("%i ", arr[i]);
	}
}
void Reverce(int arr[], int left, int right) {
	int k = right,s=0,g=right+left;
	/*if (left >= right / 2) {
		g = right + left;
	}*/
	for (int i = left;i < (g/2+g%2);i++) {
		s = arr[i];
		arr[i] = arr[k - 1];
		arr[k - 1] = s;
		k = k - 1;
		s = 0;
	}
	//Print(arr, 9);
	//printf("\n");
}
void Shift_Ver2(int arr[], int size, int delta) {
	int p = size - delta;
	Reverce(arr, 0, size);
	Reverce(arr, 0,size-delta);
	Reverce(arr, p, size);
}
int main(void) {
	int arr[N], delta;
	setlocale(LC_CTYPE, "Russian");
	Fill(arr, N);
	Print(arr, N);
	printf("\n");

		printf("¬ведите сдвиг: ");
		scanf("%i", &delta);
		if (delta < 0) {
			while (delta < 0) {
				printf("¬ведите сдвиг: ");
				scanf("%i", &delta);
			}
		}
		delta = delta % N;
		//Reverce(arr,1,4);
		Shift_Ver2(arr, N, delta);
		Print(arr, N);
		printf("\n");
	
}