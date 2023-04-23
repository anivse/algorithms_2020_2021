#include <stdio.h>
#include "labengine.h"
#include <math.h>
#include <windows.h>
#define pi 3.14159265358979323
typedef struct {
    double x, y;
}point_t;
typedef struct {
    point_t p1, p2;
}rect_t;
typedef struct {
    double x, y;
}vect_t;
point_t Transform(point_t p, rect_t const* from, rect_t const* to) {
    point_t p0;
    p0.x = (((p.x - from->p1.x) * (to->p2.x - to->p1.x)) / (from->p2.x - from->p1.x)) + to->p1.x;
    p0.y = (((p.y - from->p1.y) * (to->p2.y - to->p1.y)) / (from->p2.y - from->p1.y)) + to->p1.y;
    return p0;
}
vect_t VectTransform(vect_t p, rect_t const* from, rect_t const* to) {
    vect_t p0;
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
void DrawAnalyticalPath(rect_t const* math,rect_t const* screen,vect_t r0,vect_t v0,vect_t a0,double dt) {
    vect_t r1=r0;
    vect_t r2;
    vect_t p1;
    vect_t p2;
    vect_t value;
    double abs_a0 = sqrt(a0.x * a0.x + a0.y * a0.y);
    double timemax = 2 * v0.y / abs_a0;
    for (double time = 0;time < timemax;time += dt) {
        r2.x = r0.x + v0.x * time + 0.5 * a0.x * time * time;
        r2.y = r0.y + v0.y * time + 0.5 * a0.y * time * time;
        value = r2;
        p1 = VectTransform(r1, math, screen);
        p2 = VectTransform(r2, math, screen);
        LabDrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
        r1 = value;
    }
}
void DrawEulerPath(rect_t const* math, rect_t const* screen, vect_t r0, vect_t v0, vect_t a0, double dt) {
    vect_t r1 = r0;
    vect_t r2 ;
    vect_t p1;
    vect_t p2;
    vect_t value;
    double abs_a0 = sqrt(a0.x * a0.x + a0.y * a0.y);
    double timemax = 2 * v0.y / abs_a0;
    vect_t dv,dr,v=v0;
    dv.x = a0.x * dt;
    dv.y = a0.y * dt;
    for (double time = 0;time < timemax;time += dt) {
        r2.x = r1.x + v.x * dt;
        r2.y = r1.y + v.y * dt;
        value = r2;
        p1 = VectTransform(r1, math, screen);
        p2 = VectTransform(r2, math, screen);
        LabDrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
        r1 = value;
        v.x += dv.x;
        v.y += dv.y;
    }
}
void SimplateEulerPath(rect_t const* math, rect_t const* screen, vect_t r0, vect_t v0, vect_t a0) {
    vect_t r1 = r0;
    vect_t r2;
    vect_t p1;
    vect_t p2;
    vect_t value;
    double abs_a0 = sqrt(a0.x * a0.x + a0.y * a0.y), dt;
    LARGE_INTEGER T1, T2, performanceCounter;
    QueryPerformanceFrequency(&performanceCounter);
   /* QueryPerformanceCounter(&T1);
    QueryPerformanceCounter(&T2);
    dt = (double)(T2.QuadPart - T1.QuadPart);*/
    vect_t dv, dr, v = v0;
    /*dv.x = a0.x * dt;
    dv.y = a0.y * dt;*/
    QueryPerformanceCounter(&T1);
    do {
        QueryPerformanceCounter(&T2);
        dt = (double)(T2.QuadPart - T1.QuadPart)/performanceCounter.QuadPart*1000;
       // printf("%lf ", dt);
        dv.x = a0.x * dt;
        dv.y = a0.y * dt;
        r2.x = r1.x + v.x * dt;
        r2.y = r1.y + v.y * dt;
        value = r2;
        p1 = VectTransform(r1, math, screen);
        p2 = VectTransform(r2, math, screen);
        LabDrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
        LabDrawFlush();
        LabDelay(40);
        r1 = value;
        v.x += dv.x;
        v.y += dv.y;
        QueryPerformanceCounter(&T1);
    } while (r2.x >= 0);
}
int main() {
    if (LabInit())
    {
        // Узнать размеры окна
        int width = LabGetWidth();
        int height = LabGetHeight();
        rect_t math = { -3,28,41,-5 };
        rect_t screen = { 0,0,width,height };
        vect_t r0 = { 0,0 };
        vect_t v0 = { 20 * cos(pi / 3),20 * sin(pi / 3) };
        vect_t g = { 0,-9.8 };
        DrawAxes(&math, &screen);
        LabSetColor(LABCOLOR_GREEN);
        DrawAnalyticalPath(&math, &screen, r0, v0, g, 0.1);
        LabDrawFlush();
        LabSetColor(LABCOLOR_RED);
         DrawEulerPath(&math, &screen, r0, v0, g, 0.5);
        LabDrawFlush();
        LabSetColor(LABCOLOR_YELLOW);
      //  SimplateEulerPath(&math, &screen, r0, v0, g);
        // Отобразить картинку в окне
        LabDrawFlush();
        // Подождать нажатия клавиши и закончить работу
        LabInputKey();
        LabTerm();
    }
}