#include "Ray.h"


Ray::Ray(Vec o_, Vec d_) : o(o_), d(d_) 
{
	o = o_;
	d = d_.norm();
}

Ray::Ray()
{
	o = Vec();
	d = Vec(1);
}

Ray::~Ray()
{
}

Vec Ray::getPoint(double t)
{
	return o + d*t;
}

Ray::Ray(Vec o, Vec d, char s)
{
	this->o = o;
	this->d = d;
}
