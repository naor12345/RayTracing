#pragma once
#include <random>
#define M_PI       3.14159265358979323846

double erand48();
int toInt(double x);
double clamp(double x);

void savebmp(unsigned char * pdata, char * bmp_file, int width, int height);