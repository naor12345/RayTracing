#pragma once
#include "Geometry.h"
#include "RecPlane.h"
class Hexahedron: public Geometry
{
public:
	Hexahedron(Vec p1, Vec p2, Vec n, Vec p);
	Hexahedron(Vec p1, Vec p2, Vec n, Vec p, Vec emit, Vec color, int ref);
	~Hexahedron();

	virtual bool isOn(const Vec &P) const;
	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual IntersecResult isIntersected(Ray &ray, double radius);
	int getGeometry(Vec &hitpoint) const;
	RecPlane getRecPlane(int i) const;
private: 
	//Vec p1, p2, p, n;
	RecPlane r1, r2, r3, r4, r5, r6;
};

