#pragma once

#include "Geometry.h"

class Cylinder:public Geometry
{
public:
	Cylinder();
	~Cylinder();

	Cylinder(Vec p1, Vec p2, double radius);
	Cylinder(Vec p1, Vec p2, double radius, Vec emit, Vec color, int ref);

	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray, double s);
	Vec getPointO(Vec P, double &labmda) const;	
	char getGeometry(Vec hitpoint) const;
	bool isTall(double lambda);

private: 
	Vec p1;
	Vec p2;
	double radius;
	double h;
};

