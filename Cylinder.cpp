#include "Cylinder.h"
#include "CylinderInf.h"
#include "Plane.h"
#include "Union.h"



Cylinder::Cylinder()
{
}


Cylinder::~Cylinder()
{
}

Cylinder::Cylinder(Vec p1, Vec p2, double radius)
{
	this->p1 = p1;
	this->p2 = p2;
	this->radius = radius;
	this->h = p1.dist(p2);
}

Vec Cylinder::getPointO(Vec P, double &lambda) const
{
	lambda = (-p1.dot(p1) + p1.dot(p2) + P.dot(p1) - P.dot(p2))
		/ (p2.dot(p1) - p2.dot(p2) - p1.dot(p1) + p1.dot(p2));
	return (p2 - P) * lambda + (p1 - P) * (1 - lambda) + P;
}

Cylinder::Cylinder(Vec p1, Vec p2, double radius, Vec emit, Vec color, int ref)
{
	this->p1 = p1;
	this->p2 = p2;
	this->radius = radius;
	this->emit = emit;
	this->color = color;
	this->ref = ref;
	this->h = p1.dist(p2);
}

IntersecResult Cylinder::isIntersected(Ray &ray, double s)
{
	return isIntersected(ray);
}

IntersecResult Cylinder::isIntersected(Ray &ray)
{
	IntersecResult result = IntersecResult();
	IntersecResult minResult = IntersecResult();
	minResult.distance = 1e30;
		
	Plane plane1 = Plane(p1, (p1 - p2), emit, color, ref);
	Plane plane2 = Plane(p2, (p2 - p1), emit, color, ref);
	CylinderInf cy = CylinderInf(p1, p2, radius, emit, color, ref);
	
	result = plane1.isIntersected(ray, radius);
	if (result.isHit && result.distance < minResult.distance)
	{
		minResult = result;
		minResult._object = this;
	}
	result = plane2.isIntersected(ray, radius);
	if (result.isHit && result.distance < minResult.distance)
	{
		minResult = result;
		minResult._object = this;
	}
	result = cy.isIntersected(ray, radius);
	if (result.isHit && result.distance < minResult.distance)
	{
		minResult = result;
		minResult._object = this;
	}

	return minResult;
}

bool Cylinder::isTall(double lambda)
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

Ray Cylinder::getReflection(Ray ray, Vec hitpoint) const
{
	char r = getGeometry(hitpoint);
	if (r == 'c')
	{
		CylinderInf cy = CylinderInf(p1, p2, radius, emit, color, ref);
		return cy.getReflection(ray, hitpoint);
	}
	else if (r == '1')
	{
		Plane plane1 = Plane(p1, (p1 - p2), emit, color, ref);
		return plane1.getReflection(ray, hitpoint);
	}
	else
	{
		Plane plane2 = Plane(p2, (p2 - p1), emit, color, ref);
		return plane2.getReflection(ray, hitpoint);
	}
}

Ray Cylinder::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	char r = getGeometry(hitpoint);
	if (r == 'c')
	{
		CylinderInf cy = CylinderInf(p1, p2, radius, emit, color, ref);
		return cy.getRefraction(ray, hitpoint, Re);
	}
	else if (r == '1')
	{
		Plane plane1 = Plane(p1, (p1 - p2), emit, color, ref);
		return plane1.getRefraction(ray, hitpoint, Re);
	}
	else
	{
		Plane plane2 = Plane(p2, (p2 - p1), emit, color, ref);
		return plane2.getRefraction(ray, hitpoint, Re);
	}
}

char Cylinder::getGeometry(Vec hitpoint) const
{
	Plane plane1 = Plane(p1, (p2 - p1));
	Plane plane2 = Plane(p2, (p2 - p1));	

	if (plane1.isOn(hitpoint))
	{
		return '1';
	}
	else if (plane2.isOn(hitpoint))
	{
		return '2';
	}
	else
	{
		return 'c';
	}
}

bool Cylinder::isOn(const Vec &P) const
{
	double lambda;
	Vec o = getPointO(P, lambda);

	if (lambda > 1 || lambda < 0)
	{
		return false;
	}
	else
	{
		if (o.dist(P) < radius)
		{
			Plane plane1 = Plane(p1, (p2 - p1));
			Plane plane2 = Plane(p2, (p2 - p1));
			if (plane1.isOn(P))
			{
				return true;
			}
			else if (plane2.isOn(P))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (o.dist(P) == radius)
		{
			return true;
		}
		else return false;
	}
}