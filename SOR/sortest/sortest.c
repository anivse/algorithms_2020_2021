#include <stdio.h>
#include "sor.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#pragma warning(disable:6386)

#define MIN_SIZE 100 // ����������� ������ ������� ��� ��������� �����������
#define MAX_SIZE 10000
#define SIZE_STEP 100
#define REPEAT_COUNT 20 // ��, ������� ��� �� ������ ��������� ������ ���������� �� ������ ������� .....?

typedef sort_info_t* (*GetSort)(int* count); // ��� ������� 

typedef struct {
	int size;
	char const* sortName;
	clock_t time;
} table_t;

void FillRandom(int* arr,int size) {  // ������ ��������� �������� 
	for (int i = 0;i < size;i++) {
		arr[i] = rand();
	}
}

void Print(int arr[], int size) { // ������ ������� � �������
	for (int i = 0;i < size;i++) {
		printf("%i ", arr[i]);
	}
}

clock_t AverageTime(clock_t time[],int size) { //��������� �������� ������� 
	clock_t value, sum = 0;
	clock_t avTime;
	for (int i = 0;i < size;i++) {
		value = time[i];
		sum += value;
	}
	avTime =sum / size;
	return avTime;
}

table_t* CheckSorts(int size,sort_info_t* sort) { // �������� ������ ���������� �� ������ �������� 
	long tableSize = (((MAX_SIZE - MIN_SIZE) / SIZE_STEP)+2) * size * sizeof(table_t);
	table_t* sortData= malloc(tableSize);
    //table_t* sortData = malloc(tableSize); //  ������� ������� ����� � ����
	int p = 1;
	LARGE_INTEGER startSort, endSort, counter; //�����
	clock_t timeArray[REPEAT_COUNT], timeSort; // ������ ������
	int* arr = malloc(sizeof(int) * MIN_SIZE);
	int* arr1;
	QueryPerformanceFrequency(&counter);
	if (sortData) {
		for (int count = MIN_SIZE;count <= MAX_SIZE;count += SIZE_STEP) {
			for (int i = size * (p - 1),k=0;i < size * p;i++,k++) {
				sortData[i].size = count;
				sortData[i].sortName = sort[k].name;
				for (int j = 0;j < REPEAT_COUNT;j++) {
					srand((unsigned int)time(NULL)); // ���������� ������
					FillRandom(arr, count);
					QueryPerformanceCounter(&startSort);
					sort[k].sort(arr, count);
					QueryPerformanceCounter(&endSort);
					timeSort = (clock_t)((double)(endSort.QuadPart - startSort.QuadPart) / (double)counter.QuadPart * 1000);
					//printf("%lf ", timeSort);
					timeArray[j] = timeSort;
				}
				//printf("\n");
				sortData[i].time = AverageTime(timeArray,REPEAT_COUNT);
				arr1 = realloc(arr,sizeof(int) * ((long long)count + SIZE_STEP));
				if (arr1!=NULL) {
					arr = arr1;
				}
			}
			p++;
		}
	}
	free(arr);
	return sortData;
}
int compare(const void* x1, const void* x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);   // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

clock_t* ReferenceSort() {
	clock_t* timeQsort = malloc((((MAX_SIZE - MIN_SIZE) / SIZE_STEP) + 2) * sizeof(double)); // ��� ������� qsort
	int* arr = malloc(sizeof(int) * MIN_SIZE);
	int* arr1;
	LARGE_INTEGER startSort, endSort,counter; //�����
	clock_t timeArray[REPEAT_COUNT], timeSort; // ������ ������
	QueryPerformanceFrequency(&counter);
	if (arr) {
		if (timeQsort) {
			for (int count = MIN_SIZE, i = 0;count <= MAX_SIZE;count += SIZE_STEP, i++) {
				for (int j = 0;j < REPEAT_COUNT;j++) {
					srand((unsigned int)time(NULL)); // ���������� ������
					FillRandom(arr, count);
			        QueryPerformanceCounter(&startSort);
					qsort(arr, count, sizeof(int), compare);
				    QueryPerformanceCounter(&endSort);
					timeSort = (clock_t)((double)(endSort.QuadPart - startSort.QuadPart)/(double)counter.QuadPart*1000);
					timeArray[j] = timeSort;
				}
				timeQsort[i] = AverageTime(timeArray, REPEAT_COUNT);
				//printf("%lf ", timeQsort[i]);
				arr1 = realloc(arr, sizeof(int) * ((long long)count + SIZE_STEP));
				if (arr1 != NULL) {
					arr = arr1;
				}
			}
			//Print(timeQsort, (MAX_SIZE - MIN_SIZE) / SIZE_STEP);
		}
	}
	return timeQsort;
}

void FileWrite(char const* filename, int countSort, table_t* sort,int step) { // ����� � ������ countSort - ���-�� ����� ����������, step - ���������� �������� �������� 
	FILE* file = fopen(filename, "w");
	int p = 0;
	if (file) {
		fprintf(file, "Array size;");
		clock_t* refTime = ReferenceSort();
		for (int i = 0;i < countSort;i++) {
			fprintf(file, "%s;", sort[i].sortName);
		}
		fprintf(file, "Reference sort;");
		fprintf(file, "\n");
		for (int i = 0;i < step;i++) {
			fprintf(file, "%i;", sort[i * countSort].size);
			for (int j = i * countSort;j < (i + 1) * countSort;j++) {
				//printf("%i\n", j);
				//fprintf(file, "%s;", sort[j].sortName);
				fprintf(file, "%li;", sort[j].time);
				//puts("good");
			}
			fprintf(file, "%li;", refTime[i]);
			fprintf(file,"\n");
		}
		fclose(file);
		free(refTime);
	}
}

int main() {
	
	HINSTANCE hDLL; 
	int counter;
	sort_info_t* sort; // ��������� �� �������
	hDLL = LoadLibrary(L"SOR.dll"); // ����������� ���������
	if (hDLL!=NULL) {
		GetSort dllSort = (GetSort)GetProcAddress(hDLL, "GetSortList"); //��������� ������ �������
		if (dllSort != NULL) {
		    sort = dllSort(&counter); //���������� GetSortList
			table_t* sortData = CheckSorts(counter, sort); // ������� �������� counter - ���������� ����� ����������, sort - ����������
			FileWrite("sorttable.csv", counter, sortData, ((MAX_SIZE-MIN_SIZE)/SIZE_STEP)+1); //������ � ���� 

			free(sortData);
		}
		else
		{
			sort =(sort_info_t*) ERROR_DELAY_LOAD_FAILED;
		}
		FreeLibrary(hDLL);
	}
	else
	{
		sort =(sort_info_t*) ERROR_DELAY_LOAD_FAILED;
	}
	
		return 0;
  /*HMODULE hInst=LoadLibrary(L"SOR.dll");
  int s=0;
  if (hInst == 0) {
	  perror("No");
  }
	  FARPROC fn = GetProcAddress(hInst, "GetSortList");
	  if (fn == 0) {
		  FreeLibrary(hInst);
	  }
	  sort_info_t* sort = GetSortList(&s);
	  printf("%i", s);
 */
}