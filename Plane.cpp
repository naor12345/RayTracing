#include "Plane.h"


Plane::Plane(Vec p, Vec normV)
{
	this->p = p; 
	this->normV = normV.norm();
}

Plane::Plane(Vec p, Vec normV, Vec emit, Vec color, int ref)
{
	this->p = p;
	this->normV = normV.norm();
	this->emit = emit;
	this->color = color;
	this->ref = ref;
}

Plane::~Plane()
{
}

IntersecResult Plane::isIntersected(Ray &ray, double radius)
{
	IntersecResult result = IntersecResult();

	double m = ray.d.dot(normV);
	double det = (p - ray.o).dot(normV);

	if (m == 0)
	{
		return result;
	}
	else if (det / m <= 0)
	{
		return result;
	}
	else
	{
		result.isHit = 1;		
		result.distance = det / m;
		result.position = ray.getPoint(result.distance);

		if (p.dist(result.position) > radius)
		{
			result = IntersecResult();
		}
		else
		{
			if (normV.dot(ray.d) < 0)
			{
				result.normal = normV;
			}
			else
			{
				result.normal = normV * -1;
			}			
		}
		return result;
	}
}

IntersecResult Plane::isIntersected(Ray &ray)
{	
	IntersecResult result = IntersecResult();

	double m = ray.d.dot(normV);
	double det = (p - ray.o).dot(normV);

	if (m == 0)
	{
		return result;
	}
	else if (det / m <= 0)
	{
		return result;
	}
	else
	{
		result.isHit = 1;
		result._object = this;
		result.distance = det / m;
		result.position = ray.getPoint(result.distance);
		if (normV.dot(ray.d) < 0)
		{
			result.normal = normV;
		}
		else
		{
			result.normal = normV * -1;
		}
		return result;
	}
}

Ray Plane::getReflection(Ray ray, Vec hitpoint) const
{
	Vec n = normV;
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

double Plane::dist(const Vec &P) const
{
	return abs(normV.dot(P - p));
}

Vec Plane::distP(const Vec &P)
{
	double d = normV.dot(P - p);
	return (P - normV*d);
}

Ray Plane::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	// norm direction is plus direction
	Vec n = normV;
	Vec nl = n.dot(ray.d) < 0 ? n : n*-1;
	bool into = n.dot(nl) > 0;

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

bool Plane::isOn(const Vec &P) const
{
	if (P.x == p.x && P.y == p.y && P.z == p.z)
	{
		return true;
	}
	/*if ((P-p).dot(normV) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/

	if (dist(P) < 1e-4)
	{
		return true;
	}
	else
	{
		return false;
	}
}