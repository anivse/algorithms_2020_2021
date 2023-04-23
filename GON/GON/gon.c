#include <stdio.h>
#include <math.h>
#include "labengine.h"
#define pi 3.14
typedef struct {
	int x0, y0;
	int number;
	int radius;
}gon_t;
//void DrawGon(int number, int radius, double alfa, int x0, int y0) {
//	double beta = 0;
//	for (int i = 0;i < number;i++) {
//	//	LabDrawLine(x0, y0, (int)(x0 + radius * cos(alfa + beta)), (int)(y0 + radius * sin(alfa + beta)));
//		LabDrawLine((int)(x0 + radius * cos(alfa + beta)), 
//			(int)(y0 + radius * sin(alfa + beta)), 
//			    (int)(x0 + radius * cos(alfa + beta+6.28/number)), 
//			        (int)(y0 + radius * sin(alfa +  beta+6.28/number)));
//		beta = beta + 6.28 / number;
//	}
//}

void DrawGon(double alfa, gon_t gon) {
	double beta = 0;
	for (int i = 0; i < gon.number; i++) {
		LabDrawLine((int)(gon.x0 + gon.radius * cos(alfa + beta)), 
	        (int)(gon.y0 + gon.radius * sin(alfa + beta)), 
			    (int)(gon.x0 + gon.radius * cos(alfa + beta + 2 * pi / gon.number)),
			        (int)(gon.y0 + gon.radius * sin(alfa + beta + 2 * pi / gon.number)));
		beta = beta + 2 * pi / gon.number;
	}
}

int main(void) {
	if (LabInit()) {
		int width = LabGetWidth();
		int height = LabGetHeight();
		double angle = 0.0;
		gon_t gon = { width / 2, height / 2, 6, height / 2 };
		LabSetColor(LABCOLOR_BLUE);
		while (LabInputKeyReady() == LAB_FALSE) {
			LabClear();
			//DrawGon(6, height / 2, ugol, width / 2, height / 2);
			DrawGon(angle, gon);
			LabDrawFlush();
			LabDelay(100);
			angle -= 0.1;
		}
		LabInputKey();
		LabTerm();
	}
}