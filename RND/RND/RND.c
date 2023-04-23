#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/**
 * ���������� ������������ ��������� �����, ���������� �������������
 * �� ������������ ��������� [a, b).
 *
 * @param a  ������ �������
 * @param b  ������� �������
 *
 * @return ��������� ����� �� a �� b (�� ������� ������� �������).
 */
double Random(double a, double b)
{
	// TODO: 1. ��������� �������.
	int k;
	double q;
	k = rand();
	q = ((double)k)/ (RAND_MAX + 1);
	q = q * (b - a)+a;
	//q += a;
	return q;
}

/**
 * ��������� ������ ���������� �������������� ���������� �������.
 *
 * @param arr   ������
 * @param size  ���������� ��������� � �������
 * @param a     ������ �������
 * @param b     ������� ������� (�� ���������� � ��������)
 *
 * @see Random()
 */
void FillRandom(double arr[], int size, double a, double b)
{
	// TODO: 1. ��������� �������.
	for (int i = 0;i < size;i++) {
		arr[i] = Random(a, b);
	}
}

/**
 * �������� �������� ������� ����� ������� � �������� �������.
 *
 * @param arr   ������
 * @param size  ���������� ��������� � �������
 */
void Print(double const arr[], int size)
{
	// TODO: 1. ��������� �������.
	printf("{");
	for (int i = 0;i < size;i++) {
		printf("%lf", arr[i]);
		if (i < size - 1) 
			printf(", ");
	}
	printf("}");
}

//////////////////////////////////////////////////////////////////////////////

/**
 * ������ ����������� �������� ��������� �������.
 *
 * ��������� ������ counters[] �� ��������� �������� ��������� ������� arr[],
 * �����������, ������� �� ������ � ��������������� �����������
 * ������� ��������� [a, b). �������� �������, �� ���������� � ���������
 * �������� �� a �� b ������������.
 *
 * @param arr       ������
 * @param size      ���������� ��������� � �������
 * @param a         ������ �������
 * @param b         ������� ������� (�� ���������� � ��������)
 * @param counters     ����������� ������
 * @param numCounters  ���������� ������������� ��������
 */
void BuildHistogram(double const arr[], int size,
	double left, double right, int counters[], int numCounters)
{
	// TODO: 2. ��������� ������ ��� �����������.
	double q,s;
	double p;
	int w;
	for (int i = 0;i < numCounters;i++) {
		counters[i] = 0;
	}
	for (int i = 0;i < size;i++) {
		q = arr[i] - left;
		q = q / (right - left);
		q = q * numCounters;
		s = modf(q, &p);
		//printf("%lf ", p);
		w = p;
		//printf("%i  ", w);
		counters[w]++;
	}
}

/**
 * �������� �������� ������� ����� ������� � �������� �������.
 *
 * @param counters     ������
 * @param numCounters  ���������� ��������� � �������
 */
void PrintHistogram(int counters[], int numCounters)
{
	// TODO: 2. ��������� ������ ��� �����������.
	printf("{");
	for (int i = 0;i < numCounters;i++) {
		printf("%i", counters[i]);
		if (i < numCounters - 1)
			printf(", ");
	}
	printf("}");
	printf("\n");
}

#define HIST_CHAR_BAR    'o'
#define HIST_CHAR_SPACE  183

int maximal(int counters[], int numCounters) {
	int k = 1, s;
	for (int i = 0;i < numCounters;i++) {
		if (counters[i] > counters[k]) {
			k = i;
		}
	}
	s = counters[k];
	return s;
}

/**
 * �������� �������������� ����������� �������� ��������� �������.
 *
 * @param counters     ������ ����������, ���������� ���������� ���������,
 *                  �������� � ��������������� �����������
 * @param numCounters  ���������� ������������� ��������
 * @param width     ������ ������ ���� ������ �����������, � �����������
 */
void DrawHistogram(int counters[], int numCounters, int width)
{
	// TODO: 3. ��������� ���������.
	int max = maximal(counters, numCounters);
	int column;
	for (int i = 0;i < numCounters;i++) {
		column = width * counters[i] / max;
		printf("%2i ", i + 1);
		for (int j = 0;j < column;j++) {
			printf("%c",HIST_CHAR_BAR);
		}
		for (int k = column;k < width;k++) { 
			printf("%c", HIST_CHAR_SPACE);
		}
		printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////////////

int main(void)
{
	const int PRINT_MAX = 20;
	const double RANDOM_MIN = 0.2;
	const double RANDOM_MAX = 0.6;
	const double HIST_MIN = 0.0;
	const double HIST_MAX = 0.8;
	const int HIST_LINES = 5;
	const int HIST_LENGTH = 16;

	int size = 10;
	double* numbers = NULL;
	int* hist = NULL;

	setlocale(LC_CTYPE, "Russian");

	// TODO: 0. �������� �� ��������� �����. ����������� ��������� � �����.
	// ��� ������� ����� ��������������� ���� ������� ������ ������
	srand((unsigned)time(0));
	for (int i = 0;i < 10;i++) {
		printf("%i ", rand() );
	}
	// ...


	// ������������� � ������������
	printf("\n������� ���������� �����: ");
	scanf("%i", &size);

	// �������� ������
	numbers = malloc(size * sizeof(double));
	hist = malloc(HIST_LINES * sizeof(int));

	// ��������� �������
	printf("\n����������� �� (������ %i �����):\n", PRINT_MAX);
	FillRandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	Print(numbers, size < PRINT_MAX ? size : PRINT_MAX);
	printf("\n");

	// ��������� ����������� ����������� ��������� ��������
	BuildHistogram(numbers, size, HIST_MIN, HIST_MAX, hist, HIST_LINES);
	PrintHistogram(hist, HIST_LINES);
	DrawHistogram(hist, HIST_LINES, HIST_LENGTH);

	// ���������� ������
	free(hist);
	free(numbers);

	return 0;
}