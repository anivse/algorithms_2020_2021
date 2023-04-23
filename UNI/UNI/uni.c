#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<math.h>
#pragma warning(disable:4996)
typedef enum {
	RED,
	GREEN,
	BLUE,
	COLOR_COUNT,
}color_t;
typedef enum {
	CIRCLE,
	RECTANGLE,
	POLYGON,
	TYPE_COUNT,
}type_t;
typedef struct {
	float radius;
}circle_t;
typedef struct {
	float width, height;
}rectangle_t;
typedef struct {
	int number;
	float length;
}polygon_t;
typedef union {
	circle_t circle;
	rectangle_t rectangle;
	polygon_t polygon;
}size_figure_t;
typedef struct {
	type_t figure;
	color_t color;
	size_figure_t size_figure;
}figure_t;

figure_t* ReadBinary(char const* filename,int* number) {
	FILE* file;
	int size;
	figure_t* arr;
	file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	arr = malloc(size);
	*number = size / sizeof(figure_t);
	fread(arr, sizeof(figure_t), *number, file);
	fclose(file);
	return arr;                                             
}
void NumberTypes(figure_t* arr,int size) {
	int cir=0,rec=0,pol=0,k=0;
	float square=0,sqc=0,sqr=0,sqp=0;
	for (int i = 0;i < size;i++) {
		if (arr[i].figure == CIRCLE) {
			cir++;
			sqc = 3.14* (arr[i].size_figure.circle.radius) * (arr[i].size_figure.circle.radius);
			square += sqc;
		}
		if (arr[i].figure == RECTANGLE) {
			rec++;
			sqr =(arr[i].size_figure.rectangle.height) * (arr[i].size_figure.rectangle.width);
			square += sqr;
		}
		if (arr[i].figure == POLYGON) {
			pol++;
			sqp =((arr[i].size_figure.polygon.number) * (arr[i].size_figure.polygon.length) * (arr[i].size_figure.polygon.length)) / (4 * tan(180 / (arr[i].size_figure.polygon.number)));
			square += sqp;
		}
		//square = sqc + sqp + sqr;
		k++;
	}
	printf("Types:\nCIRCLE=%i\nRECTANGLE=%i\nPOLYGON=%i\n", cir, rec, pol);
	printf("\n\nSquare= %.2f\n\n", square);
	//printf("%i\n", k);
}
void NumberColor(figure_t* arr, int size) {
	int red = 0, gre = 0, blu = 0;
	for (int i = 0;i < size;i++) {
		if (arr[i].color == RED)
			red++;
		if (arr[i].color == GREEN)
			gre++;
		if (arr[i].color == BLUE)
			blu++;
	}
	printf("Color:\nRED=%i\nGREEN=%i\nBLUE=%i\n", red, gre, blu);
}
int main(void) {
	figure_t* figures;
	int size=0;
	figures= ReadBinary("uni_shapes_1.bin",&size);
	printf("Size array:%i \n", size);
	NumberTypes(figures,size);
	NumberColor(figures, size);
	free(figures);
}