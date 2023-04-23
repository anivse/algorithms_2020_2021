#include <stdio.h>
#include <locale.h>
#define LENGTH 100
#pragma warning(disable:4996)
int len(char const str[]) {
	int i = 0;
	do {
		i++;
	} while (str[i] != '\0');
	return i;
}
int Kolvo(char str[], int length) {
	int i = 0, n = 0, k = 0, m = 0, p = 0,a=0,q=0,x=0;
	for (int s = 0;s < length;s++) {
		for (int i =a ;i < length;i++) {
			if (str[i] == '/') {
				while (str[i] == '/') {
					i++;
				}
				if (str[i] == '*') {
					k++;
					p = i+1;
					for (int x = p;x < length;x++) {
						if (str[x] == '*') {
							while (str[x] == '*') {
								x++;
							}
							if (str[x] == '/') {
								a = x+1;
								//printf("%i\n", a);
								m++;
								q = k;
								for (int j = 0;j < length;j++) {
									x++;
								}
								x = length-1;
								i = length-1;
							}
						}
					}

				}
			}


		}
	}
	return q;
}
void RemoveComments(char str[], int  length) {
	int  k=0;
	k = Kolvo(str,length);
	//printf("%i\n", k);
	for (int i = 0;i < k;i++) {
		int  K, M, P,S=0, V=0, i = 0, s = 0, d = 0;
		char str3[LENGTH] = { 0 };
		//puts(str);
					for (int i = 0;i < LENGTH;i++) {
						if (str[i] == '/') {
							while (str[i] == '/') {
								i++;
							}
							if (str[i] == '*') {
								s = i;
								for (int m = 0;str[i - 1] != '\0';m++){
									i++;
									V = m + 1;
								}
							}
							
						}
					}
					//printf("\n");
					//printf("s=%i", s);
				   // printf("\n");
				     P = len(str);
					//printf("P=%i\n", P);
					M = P - V;
					//printf("M=%i\n", M);
				   // printf("str3= ");
					for (int a = s;a < LENGTH;a++) {
						if (str[a] == '*') {
							while (str[a] == '*') {
								a++;
							}
							if (str[a] == '/') {
								for (int K = 0;str[a + 1] != '\0';K++) {
									str3[K] = str[a + 1];
									//printf("%c", str3[K]);
									a++;
									V = K + 1;
								}
								a = LENGTH - 1;
							}
						}
					}
					str3[V] = '\0';
				//	printf("\n");
					//puts(str3);
					//printf("\n");
				//	printf("V=%i\n",V);
				//	puts(str);
				//	printf("\n");
					K = M;
				//	printf("%i", K);
				//	printf("  ");
					for (int m = 0;(m < V);m++) {
						str[K] = str3[m];
					//	printf("%c", str[K]);
						K++;
					}
					str[K] = '\0';
				//	printf("\n");
				//	puts(str);
				//	printf("\n");
	}
}
int main(void){
	int n=0,k=0;
	char str[LENGTH];
	setlocale(LC_CTYPE,"Russian");
	do {
		printf("¬ведите строку:  ");
		gets(str);
		n = len(str);
		k = Kolvo(str, n);
		//printf("%i\n", k);
		if (k != 0) {
			RemoveComments(str, n);
			puts(str);
		}
		else puts(str);
		printf("\n");
	} while (str[0] != '\0');
	return 0;
}