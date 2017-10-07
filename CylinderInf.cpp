#include "CylinderInf.h"
#include "Sphere.h"
#include "Plane.h"


CylinderInf::CylinderInf()
{
}


CylinderInf::~CylinderInf()
{
}

CylinderInf::CylinderInf(Vec p1, Vec p2, double radius)
{
	this->p1 = p1;
	this->p2 = p2;
	this->radius = radius;
}

CylinderInf::CylinderInf(Vec p1, Vec p2, double radius, Vec emit, Vec color, int ref)
{
	this->p1 = p1;
	this->p2 = p2;
	this->radius = radius;
	this->emit = emit;
	this->color = color;
	this->ref = ref;
}

IntersecResult CylinderInf::isIntersected(Ray &ray, double s)
{
	Vec dn, dt;
	Vec n = p1 - p2;

	double lambda;
	n = (n.dot(ray.d) < 0) ? (n*-1).norm() : n.norm();
	dn = n * ray.d.dot(n);
	dt = ray.d - dn;
	//Ray rdt = Ray(ray.o, dt, 's');
	Ray rdt = Ray(ray.o, dt);
	Vec o_ = getPointO(ray.o, lambda);

	Sphere oo = Sphere(o_, radius);
	IntersecResult result = oo.isIntersected(rdt);

	if (result.isHit == false)
	{
		return IntersecResult();
	}
	else
	{
		result.distance = result.distance / dt.dist(Vec());
		result.position = ray.getPoint(result.distance);
		result.normal = result.position - getPointO(result.position, lambda);
		if (!isTall(lambda))
		{

			result = IntersecResult();
		}
		else
		{
			result.normal.norm();			
		}
		return result;
	}
}

bool CylinderInf::isTall(double lambda) const
{
	if (lambda > 1 || lambda < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IntersecResult CylinderInf::isIntersected(Ray &ray)
{
	Vec dn, dt;
	Vec n = p1 - p2;
	
	double lambda;
	n = (n.dot(ray.d) < 0) ? (n*-1).norm() : n.norm();
	dn = n * ray.d.dot(n);
	dt = ray.d - dn;
	//Ray rdt = Ray(ray.o, dt, 's');
	Ray rdt = Ray(ray.o, dt);
	Vec o_ = getPointO(ray.o, lambda);

	Sphere oo = Sphere(o_, radius);
	IntersecResult result = oo.isIntersected(rdt);

	if (result.isHit == false)
	{
		return IntersecResult();
	}
	else
	{		
		result.distance = result.distance / dt.dist(Vec());
		result._object = this;
		result.position = ray.getPoint(result.distance);
		result.normal = result.position - getPointO(result.position, lambda);
		result.normal.norm();
		return result;
	}
}

Ray CylinderInf::getReflection(Ray ray, Vec hitpoint) const
{
	double lambda;
	Vec nll = hitpoint - getPointO(hitpoint, lambda);
	nll = nll.norm();	
	Plane refPlane = Plane(hitpoint, nll, emit, color, ref);
	return refPlane.getReflection(ray, hitpoint);
}

Vec CylinderInf::getPointO(Vec P, double &lambda) const
{
	lambda = (-p1.dot(p1) + p1.dot(p2) + P.dot(p1) - P.dot(p2))
		/ (p2.dot(p1) - p2.dot(p2) - p1.dot(p1) + p1.dot(p2));
	return (p2 - P) * lambda + (p1 - P) * (1 - lambda) + P;
}

Ray CylinderInf::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	double lambda;
	Vec n = (hitpoint - getPointO(hitpoint, lambda)).norm();
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

bool CylinderInf::isOn(const Vec &P) const
{
	double lambda;
	Vec o = getPointO(P, lambda);
	if (P.dist(o) == radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}