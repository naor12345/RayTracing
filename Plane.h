#pragma once
#include "Geometry.h"
class Plane:public Geometry
{
public:
	Plane(Vec p = (0, 0, 0), Vec normV = (0, 1, 0));
	Plane(Vec p, Vec normV, Vec emit, Vec color, int ref);
	~Plane();

	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray, double dist);
	double dist(const Vec &P) const;
	Vec distP(const Vec &P);

	Vec p;
	Vec normV;
};

