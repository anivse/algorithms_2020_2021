#include "fool.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
int main(void) {
	//функция FoolFromInt
	int intA=0, intB = 15;
	fool_t foolIntA = FoolFromInt(intA);
	fool_t foolIntB = FoolFromInt(intB);
	printf("function FoolFromInt:\n%i->%lf\n%i->%lf\n\n", intA, foolIntA, intB, foolIntB);
	//функция FoolFromDouble
	double doubleA = 0.55, doubleB = 0.78;
	fool_t foolDoubleA = FoolFromDouble(doubleA);
	fool_t foolDoubleB = FoolFromDouble(doubleB);
	printf("function FoolFromDouble:\n%lf->%lf\n%lf->%lf\n\n", doubleA, foolDoubleA, doubleB, foolDoubleB);
	//функция FoolAsInt
	fool_t intFoolA = 0.1, intFoolB= 0.6;
	int intFa = FoolAsInt(intFoolA);
	int intFb = FoolAsInt(intFoolB);
	printf("function FoolAsInt:\n%lf->%i\n%lf->%i\n\n",intFoolA,intFa,intFoolB,intFb);
	//функция FoolAsDouble
	fool_t doubleFoolA = 0.1, doubleFoolB = 0.18;
	double doubleFA = FoolAsDouble(doubleFoolA);
	double doubleFB = FoolAsDouble(doubleFoolA);
	printf("function FoolAsDouble:\n%lf->%lf\n%lf->%lf\n\n", doubleFoolA, doubleFA, doubleFoolB, doubleFB);
	//функция FoolParse
	char strF[] = "fool[0.15]";
	fool_t foolStr = FoolParse(strF);
	printf("function FoolParse:\n%s->%lf\n\n",strF,foolStr);
	//функция FoolFormat
	fool_t foolValue=0.7895;
	char* strFormat = FoolFormat(foolValue);
	printf("function FoolFormat:\n%lf->%s\n\n", foolValue, strFormat);
	free(strFormat);
	//функция FoolRead
	FILE* fileread = fopen("readtest.txt", "r");
	fool_t foolRead = FoolRead(fileread);
	fclose(fileread);
	printf("function FoolRead:\n%lf\n\n", foolRead);
	//функция FoolWrite
	fool_t foolWrite = 0.89475;
	FILE* filewrite = fopen("writetest.txt", "w");
	printf("function FoolWrite:\n\n");
	FoolWrite(filewrite, foolWrite);
	fclose(filewrite);
	fool_t a = 0.7, b = 0.4;
	//функция FoolAnd
	fool_t and = FoolAnd(a, b);
	printf("function FoolAnd:\n%lf and %lf=%lf\n\n", a, b, and);
	//функция FoolOr
	fool_t or = FoolOr(a, b);
	printf("function FoolOr:\n%lf or %lf=%lf\n\n", a, b, or);
	//функция FoolNot
	fool_t not= FoolNot(a);
    printf("function FoolNot:\nnot %lf=%lf\n\n", a, not);
	//функция FoolCompare
	fool_t f = 15;
	int cmp = FoolCompare(a, b);
	printf("function FoolCompare:\n%lf %lf result %i\n\n", a, b, cmp);
	FoolWrite(stdout, a);
}