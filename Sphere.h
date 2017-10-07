#pragma once
#include "Geometry.h"

class Sphere:public Geometry
{
public:
	Sphere();
	~Sphere();
	Sphere(Vec center, double radius);
	Sphere(double radius, Vec center, Vec emit, Vec color, int ref);

	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray, double s);
private:
	Vec center;
	double radius;

};

