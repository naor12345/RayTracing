#pragma once
#include "Geometry.h"

class CylinderInf:public Geometry
{
public:
	CylinderInf();
	~CylinderInf();

	CylinderInf(Vec p1, Vec p2, double radius);
	CylinderInf(Vec p1, Vec p2, double radius, Vec emit, Vec color, int ref);
	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	Vec getPointO(Vec P, double &labmda) const;
	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray, double s);
	bool isTall(double lambda) const;

private:
	Vec p1;
	Vec p2;
	double radius;	
};

