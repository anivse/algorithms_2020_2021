#include <stdio.h>
#include <math.h>
#include "labengine.h"
typedef struct {
    double x, y;
}point_t;
typedef struct {
    point_t p1, p2;
}rect_t;
point_t Transform(point_t p, rect_t const* from, rect_t const* to) {
    point_t p0;
    p0.x = (((p.x - from->p1.x) * (to->p2.x - to->p1.x)) / (from->p2.x - from->p1.x)) + to->p1.x;
    p0.y = (((p.y - from->p1.y) * (to->p2.y - to->p1.y)) / (from->p2.y - from->p1.y)) + to->p1.y;
    return p0;
}
void DrawAxes(rect_t const* math, rect_t const* screen) {
    point_t mc = { 0,0 };
    point_t cen = Transform(mc, math, screen);
    LabDrawLine((int)(screen->p1.x), (int)(cen.y), (int)(screen->p2.x), (int)(cen.y));
    LabDrawLine((int)(cen.x), (int)(screen->p1.y), (int)(cen.x), (int)(screen->p2.y));
}
labbool_t IsInsideDisk(point_t p) {
    labbool_t bool;
    /*if (((p.x <= 1) && (p.x >= -1)) && ((p.y <= 1) && (p.y >= -1))) {*/
    if ((p.x * p.x + p.y * p.y) <= 1 * 1) {
        bool = LAB_TRUE;
    }
    else
        bool = LAB_FALSE;
    return bool;
}
void DrawDisk(rect_t const* math, rect_t const* screen) {
    for (double i = screen->p1.x; i < screen->p2.x; i++) {
        for (double j = screen->p1.y; j < screen->p2.y; j++) {
            point_t p = { i,j };
            point_t pT = Transform(p, screen, math);
            if (IsInsideDisk(pT) == LAB_TRUE) {
                LabDrawPoint((int)i, (int)j);
                //LabDrawFlush();                                                                                                                                                  
            }
        }
    }
}
labbool_t IsInsideJulia(point_t p,point_t c) {
    labbool_t bool = LAB_TRUE;
   /* point_t c = { -0.12375,0.56508 };*/
    point_t z = p;
    /* printf("%lf %lf", z.x, z.y);*/
    if ((z.x * z.x + z.y * z.y) > 4) {
        bool = LAB_FALSE;
        return bool;
    }
    for (int i = 0;i < 100;i++) {
        point_t q = z;
        z.x = q.x * q.x - q.y * q.y + c.x;
        z.y = (2 * q.x * q.y) + c.y;
        /*printf("%lf %lf\n", z.x, z.y);*/
        if ((z.x * z.x + z.y * z.y) > 4) {
            bool = LAB_FALSE;
            return bool;
        }

    }
    // printf("%lf %lf\n", z.x, z.y);
    return bool;
}
void DrawJulia(point_t c,rect_t const* math, rect_t const* screen) {
    for (double i = screen->p1.x; i < screen->p2.x; i++) {
        for (double j = screen->p1.y; j < screen->p2.y; j++) {
            point_t p = { i,j };
            point_t pT = Transform(p, screen, math);
            if (IsInsideJulia(pT,c) == LAB_TRUE) {
                LabDrawPoint((int)i, (int)j);
            }
        }
    }
}
int main() {
    if (LabInit())
    {
        // Узнать размеры окна
        int width = LabGetWidth();
        int height = LabGetHeight(); 
        point_t o = { 0,0 };
        LabClearWith(LABCOLOR_CYAN);
        //point_t c = { -0.12375,0.56508 };
        rect_t math = { -2,3,2,-3 };
        rect_t screen = { 0,0,width / 2,height };
        rect_t rightscreen = { width / 2,0,width,height };
        double alfa=0;
        double r = 0.32;
        while(LabInputKeyReady() == LAB_FALSE){
            LabClear();
            LabClearWith(LABCOLOR_WHITE);
            point_t c = { r * sin(alfa),r - r * cos(alfa) };
            LabSetColor(LABCOLOR_BLACK);
            DrawAxes(&math, &screen);
            DrawAxes(&math, &rightscreen);
            LabSetColor(LABCOLOR_DARK_MAGENTA);
            DrawDisk(&math, &screen);
            DrawJulia(c, &math, &rightscreen);
            LabDrawFlush();
            LabDelay(0.05);
            alfa += 0.1;
        }
        // Отобразить картинку в окне
        LabDrawFlush();
        // Подождать нажатия клавиши и закончить работу
        LabInputKey();
        LabTerm();
    }
}