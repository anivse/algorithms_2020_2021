#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#pragma warning(disable:4996)
void FillFloats(float arr[], int length, float a, float b) {
	float k,s;
	s = a;
	k = (b - a) / length;
	for (int i = 0;i < length;i++) {
		arr[i] = s;
		s = s + k;
	}
}
void PrintFloats(float arr[], int length) {
	for (int i = 0;i < length;i++)
		printf("%f ", arr[i]);
}
void WriteText(char const* filename, float arr[], int length) {
	FILE* file;
	file = fopen(filename, "w");
	for (int i = 0;i < length;i++) {
		fprintf(file, "%2.1f ", arr[i]);
	}
	fclose(file);
}
void WriteBinary(char const* filename, float arr[], int length) {
	FILE* file;
	file=fopen(filename,"wb");
	fwrite(arr, sizeof(float), length, file);
	fclose(file);
}
float* ReadText(char const* filename, int* length) {
	FILE* file;
	float* arr,*arr1;
	arr = malloc(sizeof(float));
	int i=0;
	file = fopen(filename, "r");
	while (fscanf(file,"%f",(arr+i))!=EOF) {
		i++;
		arr1 = realloc(arr, (i + 1) * sizeof(float));
		if (arr1 != NULL)
		{
			arr=arr1;
		}
		length = (&i);
	}
	printf("\n%i", *length);
	fclose(file);
	return arr;
}
float* ReadBinary(char const* filename, int* length) {
	FILE* file;
	int size,v;
	float* arr;
	file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END); 
	size = ftell(file); 
	fseek(file, 0, SEEK_SET);
	//v = size / sizeof(float);
	length = &(size);
	printf("%i\n", *length);
	arr = calloc(size,sizeof(float));
	if(arr!=NULL)
	fread(arr, sizeof(arr), size, file);
	fclose(file);
	return arr;
}
void FileDump(char const* filename) {
	FILE* file;
     int size;
	int i = 0;
	file = fopen(filename, "rb");
	while ((size = fgetc(file))!=EOF){
		if (i % 16 == 0) {
			printf("\n");
			printf("%010x: ", ftell(file)-1);
		}
		printf("%02x ", size);
		++i;
	} 
	fclose(file);
}

int main(void) {
	float a = 0, b = 99, arr[9];
	float* text, *bin;
	int* length ;
	int N = 9;
	length = (&N);
	FillFloats(arr, 9, a, b);
	PrintFloats(arr, 9);
	WriteText("array.txt", arr, 9);
	WriteText(stdout, arr, 9);
	WriteBinary("array.bin", arr, 9);
	text = ReadText("array.txt", length);
	printf("\n");
	PrintFloats(text, 9);
	printf("\n");
	bin = ReadBinary("array.bin", length);
	PrintFloats(bin, 9);
	printf("\n");
	FileDump("array.txt");
	printf("\n");
	FileDump("array.bin");
	free(text);
	free(bin);
}