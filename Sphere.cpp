#include "Sphere.h"


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

Sphere::Sphere(Vec center, double radius)
{
	this->center = center;
	this->radius = radius;
}

Sphere::Sphere(double radius, Vec center, Vec emit, Vec color, int ref)
{
	this->center = center;
	this->radius = radius;
	this->emit = emit;
	this->color = color;
	this->ref = ref;
}

IntersecResult Sphere::isIntersected(Ray &ray, double s)
{
	return isIntersected(ray);
}

IntersecResult Sphere::isIntersected(Ray &ray)
{
	Vec op = center - ray.o;
	double t;
	double eps = 1e-4;
	double b = op.dot(ray.d.norm());
	//double b = op.dot(ray.d);
	double det = b*b - op.dot(op) + radius * radius;

	if (det < 0)
	{
		return IntersecResult();
	}
	else
	{
		det = sqrt(det);
		t = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
		if (t == 0) return IntersecResult();		
		IntersecResult result = IntersecResult();
		result.isHit = 1;
		result._object = this;
		result.distance = t;
		result.position = ray.getPoint(t);
		result.normal = result.position - center;
		result.normal.norm();
		return result;
	}
}

Ray Sphere::getReflection(Ray ray, Vec hitpoint) const
{
	Vec n = (hitpoint - center).norm();
	Vec nl = n.dot(ray.d) < 0 ? n : n*-1;
	if (ref == 0) //DIFF
	{		
		double	r1 = 2 * M_PI*erand48(),
			r2 = erand48(),
			r2s = sqrt(r2);

		Vec w = nl,
			u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).norm(),
			v = w%u;

		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1 - r2)).norm(); // reflect direction, random
		return Ray(hitpoint, d);
	}
	else
	{
		return Ray(hitpoint, ray.d - n * 2 * n.dot(ray.d));
	}
}

Ray Sphere::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	Vec n = (hitpoint - center).norm();
	Vec nl = n.dot(ray.d) < 0 ? n : n*-1;
	bool into = n.dot(nl) > 0;  	// Ray from outside going in?

	double	nc = 1,  // air
		nt = 1.5, // glass
		nnt = into ? nc / nt : nt / nc,  // relative n
		ddn = ray.d.dot(nl),    // outside: -; inside: + 1
		cos2t = 1 - nnt*nnt*(1 - ddn*ddn);
	if (cos2t < 0)    // Total internal reflection 
		return Ray(hitpoint, ray.d - n * 2 * n.dot(ray.d));

	Vec tdir = (ray.d*nnt - n*((into ? 1 : -1)*(ddn*nnt + sqrt(cos2t)))).norm();

	double	a = nt - nc,
		b = nt + nc,
		R0 = a*a / (b*b),
		c = 1 - (into ? -ddn : tdir.dot(n));

	Re = R0 + (1 - R0)*c*c*c*c*c;

	return Ray(hitpoint, tdir);
}

bool Sphere::isOn(const Vec &P) const
{
	if (P.dist(center) == radius)
	{
		return true;
	}
	else return false;
}