#include "Vec.h"


Vec::Vec(double x_, double y_, double z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Vec Vec::operator + (const Vec &b) const
{
	return Vec(x + b.x, y + b.y, z + b.z);
}

Vec Vec::operator-(const Vec &b) const
{
	return Vec(x - b.x, y - b.y, z - b.z);
}

Vec Vec::operator*(double b) const
{
	return Vec(x*b, y*b, z*b);
}

Vec Vec::operator%(const Vec &b) // cross
{
	return Vec(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
}

double Vec::dot(const Vec &b) const
{
	return x*b.x + y*b.y + z*b.z;
}

double Vec::dist(const Vec &b) const
{
	return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y) + (z - b.z)*(z - b.z));
}

Vec& Vec::norm()
{
	return *this = *this * (1 / sqrt(x*x + y*y + z*z));
}

Vec Vec::mult(const Vec &b) const
{
	return Vec(x*b.x, y*b.y, z*b.z);
}

Vec::~Vec()
{
}
