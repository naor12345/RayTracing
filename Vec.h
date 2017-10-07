#pragma once
#include <math.h>
class Vec
{
public:
	double x, y, z;
	Vec(double x_ = 0, double y_ = 0, double z_ = 0);
	Vec operator+(const Vec &b) const;
	Vec operator-(const Vec &b) const;
	Vec operator*(double b) const;
	Vec mult(const Vec &b) const;
	Vec operator%(const Vec &b); // cross
	Vec& norm();  // normalize
	double dot(const Vec &b) const;
	double dist(const Vec &b) const;

	~Vec();
};

