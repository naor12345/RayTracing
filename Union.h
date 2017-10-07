#pragma once
#include "Geometry.h"

class Union:public Geometry
{
public:
	Union();
	~Union();
	void push(Geometry *_object);
	virtual IntersecResult isIntersected(Ray &ray);
	virtual Ray getReflection(Ray ray, Vec hitpoint) const;
	virtual Ray getRefraction(Ray ray, Vec hitpoint, double &Re) const;
	virtual bool isOn(const Vec &P) const;
	IntersecResult isIntersected(Ray &ray, double s);
private:
	std::vector<Geometry*> gobjects;
};

