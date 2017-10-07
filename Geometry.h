#pragma once
#include <stdio.h>
#include "Vec.h"
#include "Ray.h"
#include "IntersectResult.h"
#include "Util.h"

class Geometry
{
public:
	Vec emit;
	Vec color;
	int ref;
	Geometry();
	~Geometry();
	virtual bool isOn(const Vec &P) const = 0;
	virtual IntersecResult isIntersected(Ray &ray) = 0;
	virtual Ray getReflection(Ray ray, Vec hitpoint) const = 0;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const = 0;
	virtual IntersecResult isIntersected(Ray &ray, double radius) = 0;
};

