#pragma once
#include "Vec.h"
class Ray
{
public:
	Vec o, d;
	Ray(Vec o_, Vec d_);
	Ray(Vec o, Vec d, char s);
	Ray();
	~Ray();
	Vec getPoint(double t);
};

