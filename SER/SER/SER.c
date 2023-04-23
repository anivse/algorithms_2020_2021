#include <stdio.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <locale.h>
#include <math.h>
void stroka(int const i) {
	printf("+");
	for (int i = 0;i < 4;i++) printf("-");
	printf("+");
	for (int i = 0;i < 10;i++) printf("-");
	printf("+");
	for (int i = 0;i < 10;i++) printf("-");
	printf("+");
	for (int i = 0;i < 10;i++) printf("-");
	printf("+");
	for (int i = 0;i < 17;i++) printf("-");
	printf("+");
	printf("\n");
}
double function(double const x) {
	double s , u;
	u = x * x;
	s = 0;
	long long i = 1;
	while(s!=s+u) {
		s = u + s;
		u = u * ((-4) * x * x) / ((2 * i + 1) * (2 * i + 2));
		i++;
	}
	return s;
}
double g1(double const a) {
	double y;
	y = sin(a) * sin(a);
	return y;
}
void PrintTable(double a, double b, int m) {
	double d=0,x, f, g, delta;
	int i = 0;
	x = a;
	stroka(i);
	printf("| i  |    x     |f(x)      |g(x)      |f(x)-g(x)        |");
	printf("\n");
	stroka(i);

	while (x<b) {
		d = fabs((b - a) / (m - 1));
		x = a + d * i;
		f = function(x);
		g = g1(x);
		delta = f - g;
		printf("|%3i |", i);
		printf("%9.6lf | ", x);
		printf("%8.6lf | ", f);
		printf("%8.6lf |  ", g);
		printf("%14.6le |", delta);
		printf("\n");
		stroka(i);
		i++;
	}
}
int main(void) {
	double a , b ;
    int  m ;
	setlocale(LC_CTYPE, "Russian");
	printf("input a ");
	scanf("%lf", &a);
	while ((a > 1) || (a < -1)) {
		printf("¬ведите значение по модулю меньшее или равное 1 ");
		scanf("%lf", &a);
	}
	printf("input b ");
	scanf("%lf", &b);
	while ((b> 1) || (b < -1)) {
		printf("¬ведите значение по модулю меньшее или равное 1 ");
		scanf("%lf", &b);
	}
	while (b < a) {
		printf("„исло b должно быть меньше числа a, input b ");
		scanf("%lf", &b);
	}
	printf("input integer m ");
	scanf("%i", &m);
	while (m <= 1) {
		printf("¬ведите значение большее 1 ");
		scanf("%i",&m);
	}
	PrintTable(a, b, m);
	return 0;
}