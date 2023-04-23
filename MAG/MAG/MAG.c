#include<stdio.h>
#include<math.h>
int main(void) {
	int N, x, i, o;
	int B[50];
	i = 0;
	x = 2;
	o = 0;
	N = 50;
	do {
		x = x * 2 + o;
		o = 0;
		B[i] = x;
		if (x >= 10) {
			x = x % 10;
			B[i] = x;
			o++;
		} 
		i++;
	} while ((i < N) && !((x == 2) && (o == 0)));
	--i;
	while (i >= 0) {
		printf("%i ", B[i]);
		i--;
	}
	return 0;
}