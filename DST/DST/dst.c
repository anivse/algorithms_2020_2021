#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<locale.h>
int len(char const *str) {
	int k = 0;
	for (int i = 1;str[i-1] != '\0';i++) {
		k = i;
	}
	return k;
}
char* Readline(void) {
	char* str=malloc(sizeof(char)),*str1;
	int i = 0;
	if (str) {
		*str = '\0';
		while ((*(str + i) = getchar()) != '\n') {
			i++;
			str1 = realloc(str, sizeof(char) * (i + 2));
			if (str1 != NULL) {
				str = str1;
			}
		}
		*(str + (i + 1)) = '\0';
		if (*(str + 0) == '\n') {
			str1 = realloc(str, sizeof(char));
			if (str1 != NULL) {
				str = str1;
			}
		}
	}
	return str;
}
char* Razdelenie(char* str,int length) {
	int k=0, s=0;
	int i = len(str);
	//printf("%i\n", i);
	char* strr = malloc(sizeof(char)*(i*3));
	if (strr) {
		*strr = '\0';
		for (int j = 0;*(str + j) != '\0';j++) {
			*(strr + k) = *(str + j);
			k++;
			s = k;
			*(strr + k) = ',';
			k++;
			*(strr + k) = ' ';
			k++;
		}
		*(strr +s) = '\0';
	}
	return strr;
}
char* Udalenie(char* str) {
	int h = len(str),s=0;
	char d;
	for (int i = 0;*(str+i)!='\0';i++) {
		d=*(str + i) ;
		s = i + 1;
		for (int j = s;*(str+j)!='\0';j++) {
			if (*(str + j) == d) {
				int p = j+1;
				while (*(str + p) == d) {
					p++;
				}
				*(str + j) = *(str + p);
			}
		}
	}
	return str;
}
//char* UniqueLetters(char const* str) {
//	char* str1;
//	int h = len(str);
//	str1 = malloc(sizeof(str[0])*h);
//	int i = 0,k=0,s=0;
//	if (str1) {
//		*str1 = '\0';
//		for (int i = 0;i<h;i++) {
//			if ((*(str + i) >= 'A') && (*(str + i) <= 'Z') || (*(str + i) >= 'a') && (*(str + i) <= 'z')) {
//				str1[k] = str[i];
//				k++;
//			}
//			s = k;
//		}
//		*(str1 + s) = '\0';
//	}
//	str1 = Udalenie(str1);
//	str1 = Razdelenie(str1);
//	return str1;
//}
char* UniqueLetters(char const* str) {
	char* str1,*str2;
	int h = len(str);
	str1 = malloc(sizeof(char)*2);
	int i = 0, k = 0, s = 0;
	if (str1) {
		*str1 = '\0';
		for (int i = 0;str[i]!='\0';i++) {
			if ((*(str + i) >= 'A') && (*(str + i) <= 'Z') || (*(str + i) >= 'a') && (*(str + i) <= 'z')) {
				str1[k] = str[i];
				k++;
				str2 = realloc(str1, sizeof(char) * (k+1));
				if (str2 != NULL) {
					str1 = str2;
				}
			}
			s = k;
		}
		*(str1 + s) = '\0';
		if (*str1 != '\0') {
			str1 = Udalenie(str1);
			str1 = Razdelenie(str1, s);
		}
	}
	return str1;
}
int main(void) {
	char* dst=NULL;
	char* str;
	setlocale(LC_CTYPE, "Russian");
	do {
		free(dst);
		dst = NULL;
		printf("¬ведите строку:   ");
		dst = Readline();
		if (*dst != '\n') {
			str = UniqueLetters(dst);
			printf("–езультат:        ");
			printf("%s", str);
			printf("\n");
			free(str);
		}
	} while (*(dst + 0) != '\n');
	free(dst);
}
	