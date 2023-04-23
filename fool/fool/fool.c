#include "fool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
fool_t FoolFromInt(int value) {
	if (value == 0) 
		return 0;
	else 
		return 1;
}
fool_t FoolFromDouble(double value) {
	if ((value <= 1) && (value >= 0)) {
		fool_t fool = value;
		return fool;
	}
	else {
		fprintf(stderr, "Invalid value\n");
		assert((value <= 1) && (value >= 0));
		perror("Invalid value");
		return -2;
	}
}
int FoolAsInt(fool_t fool) {
	if ((fool <= 1) && (fool >= 0)) {
		if (fool >= 0.5)
			return 1;
		else
			return 0;
	}
	else {
		perror("Invalid value");
		assert((fool <= 1) && (fool >= 0));
		return -2;
	}
}
double FoolAsDouble(fool_t fool) {
	if ((fool <= 1) && (fool >= 0)) {
		double value = (double)fool;
		return value;
	}
	else {
		perror("Invalid value");
		assert((fool <= 1) && (fool >= 0));
		return -2;
	}
}
fool_t FoolParse(char str[]){
	char* strFool = strstr(str, "[0.");
	if (strFool != NULL) {
		char* strChar = strchr(strFool, '0');
		char* end;
		fool_t fool = strtod(strChar, &end);

		return fool;
	}
	else {
		strFool = strstr(str, "[1]");
		if (strFool != NULL) {
			fool_t fool = 1;
			return fool;
		}
		if(strFool == NULL) {
			perror("Value not found");
			return -2;
		}
	}
}
char* FoolFormat(fool_t fool){
	if ((fool <= 1) && (fool >= 0)) {
		char* str = malloc(sizeof(fool_t) * 10);
		if (str) {
			*str = '\0';
			sprintf(str, "fool[%lf]", fool);
		}
		return str;
	}
	else {
		perror("Invalid value");
		assert((fool <= 1) && (fool >= 0));
		return -2;
	}
}
fool_t FoolRead(FILE* file) {
	if (file == stdin) {
		char* str = malloc(sizeof(char)), * str1;
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
		fool_t fool = FoolParse(str);
		free(str);
		return fool;
	}
	else {
		int size;
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* str = calloc(size, sizeof(char));
		if (str != NULL) {
			fgets(str, size, file);
		}
		fool_t fool = FoolParse(str);
		free(str);
		return fool;
	}
}
void FoolWrite(FILE* file,fool_t fool) {
	if ((fool <= 1) && (fool >= 0)) {
		fprintf(file, "fool[%lf]", fool);
	}
	else {
		perror("Invalid value");
		assert((fool <= 1) && (fool >= 0));
	}
}
fool_t FoolAnd(fool_t foolOne,fool_t foolTwo){
	if ((foolOne >= 1) || (foolOne <= 0)) {
		perror("Invalid value");
		assert((foolOne <= 1) && (foolOne >= 0));
		return -2;
	}
	if ((foolTwo >= 1) || (foolTwo <= 0)) {
		perror("Invalid value");
		assert((foolTwo <= 1) && (foolTwo >= 0));
		return -2;
	}
	if (foolOne < foolTwo) 
		return foolOne;
	else 
		return foolTwo;
}
fool_t FoolOr(fool_t foolOne,fool_t foolTwo) {
	if ((foolOne >= 1) || (foolOne <= 0)) {
		perror("Invalid value");
		assert((foolOne <= 1) && (foolOne >= 0));
		return -2;
	}
	if ((foolTwo >= 1) || (foolTwo <= 0)) {
		perror("Invalid value");
		assert((foolTwo <= 1) && (foolTwo >= 0));
		return -2;
	}
	if (foolOne > foolTwo)
		return foolOne;
	else
		return foolTwo;
}
fool_t FoolNot(fool_t fool) {
	if ((fool >= 1) || (fool <= 0)) {
		perror("Invalid value");
		assert((fool >= 1) && (fool <= 0));
		return -2;
	}
	else 
		return 1 - fool;
}
int FoolCompare(fool_t foolOne,fool_t foolTwo) {
		if (foolOne > foolTwo)
			return 1;
		if (foolOne < foolTwo)
			return -1;
		if (foolOne == foolTwo)
			return 0;
		if ((foolOne >= 1)||(foolOne <= 0)) {
			perror("Invalid value");
			assert((foolOne <= 1) && (foolOne >= 0));
			return -2;
		}
		if ((foolTwo >= 1) || (foolTwo <= 0)) {
			perror("Invalid value");
			assert((foolTwo <= 1) && (foolTwo >= 0));
			return -2;
		}
}
