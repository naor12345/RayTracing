#pragma once
#include "Geometry.h"
#include "Plane.h"
class RecPlane: public Plane
{
public:
	RecPlane(Vec p1, Vec p2, Vec p3, Vec p4, Vec p, Vec normV);
	RecPlane();
	RecPlane(Vec p1, Vec p2, Vec p3, Vec p4, Vec p, Vec normV, Vec emit, Vec color, int ref);
	~RecPlane();

	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray, double dist);

private:
	Vec p1, p2, p3, p4;
};

