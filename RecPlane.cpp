#include "RecPlane.h"


RecPlane::RecPlane(Vec p1, Vec p2, Vec p3, Vec p4, Vec p, Vec normV)
{	
	this->p = p;
	this->normV = normV.norm();
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
}

RecPlane::RecPlane() {}

RecPlane::RecPlane(Vec p1, Vec p2, Vec p3, Vec p4, Vec p, Vec normV, Vec emit, Vec color, int ref)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->p = p;
	this->normV = normV.norm();
	this->emit = emit;
	this->color = color;
	this->ref = ref;
}

RecPlane::~RecPlane()
{
}

IntersecResult RecPlane::isIntersected(Ray &ray, double dist)
{
	return isIntersected(ray);
}

IntersecResult RecPlane::isIntersected(Ray &ray)
{
	IntersecResult result = Plane::isIntersected(ray);
	if (!result.isHit)
	{
		return IntersecResult();
	}
	else
	{
		if (isOn(result.position))
		{			
			return result;
		}
		else
		{
			result = IntersecResult();
			return result;
		}
		//return result;
	}
}

Ray RecPlane::getReflection(Ray ray, Vec hitpoint) const
{
	return Plane::getReflection(ray, hitpoint);
}

Ray RecPlane::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	return Plane::getRefraction(ray, hitpoint, Re);
}

bool RecPlane::isOn(const Vec &P) const
{
	if (!Plane::isOn(P)) 
		return false;
	else
	{
		double dist = normV.dot(P - p);
		Vec p_ = P - normV*dist;
		
		

		Vec a = (p2 - p1) % (p_ - p1);
		Vec b = (p4 - p3) % (p_ - p3);
		Vec c = (p3 - p2) % (p_ - p2);
		Vec d = (p1 - p4) % (p_ - p4);

		if (a.dot(b) >= 0 && c.dot(d) >= 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}