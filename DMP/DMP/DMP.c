#include <stdio.h>
#include <locale.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
void FillInt(int a[], int size) {
	for (int i = 0;i < size;i++) {
		a[i] = 600 + i * 2;
	}
}
void FillDouble(double a[], int size) {
	double k = 0;
	for (int i = 0;i < size;i++) {
		a[i] = 600 + k;
		k = k + 2;
	}
}
void PrintInt(int a[], int size) {
	for (int i = 0;i < size;i++) {
		printf("%i ", a[i]);
	}
}
void PrintDouble(double a[], int size) {
	for (int i = 0;i < size;i++) {
		printf("%lf ", a[i]);
	}
}
void MemoryDump(void const* ptr, int size) {
	unsigned char* a = (unsigned char*)ptr;
	for (int i = 0;i < size;i++) {
		if (i % 16 == 0) {
			printf("\n");
			printf("%p: ", a + i);
		}
		printf("%02x ", *(a + i));
	}
}
int main() {
	int a[9];
	double b[9];
	FillInt(a, 9);
	PrintInt(a, 9);
	printf("\n");
	FillDouble(b, 9);
	PrintDouble(b, 9);
	printf("\n");
	MemoryDump(a, sizeof(a));
	printf("\n");
	MemoryDump(b, sizeof(b));
}
