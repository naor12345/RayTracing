#include "Union.h"


Union::Union()
{
}


Union::~Union()
{
}

void Union::push(Geometry *_object)
{
	gobjects.push_back(_object);
}

IntersecResult Union::isIntersected(Ray &ray, double radius)
{
	
	double minDistance = 1e30;
	IntersecResult minResult = IntersecResult();
	long size = this->gobjects.size();
	for (long i = 0; i < size; i++)
	{
		IntersecResult result = this->gobjects[i]->isIntersected(ray, radius);
		if (result._object != NULL && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

IntersecResult Union::isIntersected(Ray &ray)
{
	double minDistance = 1e30;
	IntersecResult minResult = IntersecResult();
	long size = this->gobjects.size();
	for (long i = 0; i < size; i++)
	{
		IntersecResult result = this->gobjects[i]->isIntersected(ray);
		if (result._object != NULL && result.distance < minDistance)
		{
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

Ray Union::getReflection(Ray ray, Vec hitpoint) const
{
	return Ray();
}
 
Ray Union::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	return Ray();
}

bool Union::isOn(const Vec &P) const
{
	return false;
}