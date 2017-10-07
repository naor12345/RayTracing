#include "Hexahedron.h"

Hexahedron::Hexahedron(Vec p1, Vec p2, Vec n, Vec p)
{
	// + direction define, out is + direction
	n = n.norm();
	Vec o = p1 * 0.5 + p2 * 0.5;
	double a = n.dot(n);
	double b = n.dot(o - p2) + (o - p1).dot(n);
	double c = (p1 - o).dot(p2 - o);

	double det = b*b - 4*a*c;

	double t = (-b + sqrt(det)) / 2 / a;

	Vec nm = (n % (p1 - p2)).norm();
	nm = (p - o).dot(nm) > 0 ? nm : nm * -1;
	double h = nm.dot(p - o);
	Vec o_ = o + nm * h;

	Vec p3 = o + n*t; Vec p4 = o - n*t;
	Vec p1_ = p1 + nm*h; Vec p2_ = p2 + nm*h;
	Vec p3_ = p3 + nm*h; Vec p4_ = p4 + nm*h;

	r1 = RecPlane(p1, p3, p2, p4, o, nm*-1, emit, color, ref); // base
	r2 = RecPlane(p1_, p3_, p2_, p4_, o_, nm, emit, color, ref); //top
	r3 = RecPlane(p1, p4, p4_, p1_, p1, (p1 - p3).norm(), emit, color, ref); //left
	r4 = RecPlane(p3, p2, p2_, p3_, p3, (p3 - p1).norm(), emit, color, ref); //right
	r5 = RecPlane(p1, p3, p3_, p1_, p1, (p1 - p4).norm(), emit, color, ref);
	r6 = RecPlane(p4, p2, p2_, p4_, p4, (p4 - p1).norm(), emit, color, ref);
}

Hexahedron::Hexahedron(Vec p1, Vec p2, Vec n, Vec p, Vec emit, Vec color, int ref)
{
	this->emit = emit;
	this->color = color;
	this->ref = ref;

	// + direction define, out is + direction
	n = n.norm();
	Vec o = p1 * 0.5 + p2 * 0.5;
	double a = n.dot(n);
	double b = n.dot(o - p2) + (o - p1).dot(n);
	double c = (p1 - o).dot(p2 - o);

	double det = b*b - 4 * a*c;

	double t = (-b + sqrt(det)) / 2 / a;

	Vec nm = (n % (p1 - p2)).norm();
	nm = (p - o).dot(nm) > 0 ? nm : nm * -1;
	double h = nm.dot(p - o);
	Vec o_ = o + nm * h;

	Vec p3 = o + n*t; Vec p4 = o - n*t;
	Vec p1_ = p1 + nm*h; Vec p2_ = p2 + nm*h;
	Vec p3_ = p3 + nm*h; Vec p4_ = p4 + nm*h;

	r1 = RecPlane(p1, p3, p2, p4, o, nm*-1, emit, color, ref); // base
	r2 = RecPlane(p1_, p3_, p2_, p4_, o_, nm, emit, color, ref); //top
	r3 = RecPlane(p1, p4, p4_, p1_, p1, (p1 - p3).norm(), emit, color, ref); //left
	r4 = RecPlane(p3, p2, p2_, p3_, p3, (p3 - p1).norm(), emit, color, ref); //right
	r5 = RecPlane(p1, p3, p3_, p1_, p1, (p1 - p4).norm(), emit, color, ref);
	r6 = RecPlane(p4, p2, p2_, p4_, p4, (p4 - p1).norm(), emit, color, ref);
}



Hexahedron::~Hexahedron()
{
}


IntersecResult Hexahedron::isIntersected(Ray &ray, double radius)
{
	return isIntersected(ray);
}

IntersecResult Hexahedron::isIntersected(Ray &ray)
{
 	IntersecResult result = IntersecResult();
	IntersecResult minResult = IntersecResult();
	minResult.distance = 1e30;

	for (int i = 1; i <= 6; i++)
	{
		result = getRecPlane(i).isIntersected(ray);
		if (result.isHit && result.distance < minResult.distance)
		{
			minResult = result;
		}
	}

	if (minResult.isHit)
	{
		minResult._object = this;
	}
	return minResult;
}

Ray Hexahedron::getReflection(Ray ray, Vec hitpoint) const
{
	int r = getGeometry(hitpoint);
	RecPlane rp = getRecPlane(r);

	return rp.getReflection(ray, hitpoint);
	//return Ray();
}

Ray	Hexahedron::getRefraction(Ray ray, Vec hitpoint, double &Re) const
{
	int r = getGeometry(hitpoint);
	RecPlane rp = getRecPlane(r);

	return rp.getRefraction(ray, hitpoint, Re);
	//return Ray();
}

int Hexahedron::getGeometry(Vec &hitpoint) const
{
	double minDist = 1e30;
	int minIdx = -1;
	for (int i = 1; i <= 6; i++)
	{
		double dist = getRecPlane(i).dist(hitpoint);
		if (dist < minDist)
		{
			minDist = dist;
			minIdx = i;
		}	
	}

	//hitpoint = getRecPlane(minIdx).dist(hitpoint);

	return minIdx;

	/*if (r1.isOn(hitpoint)) return 1;
	else if (r2.isOn(hitpoint)) return 2;
	else if (r3.isOn(hitpoint)) return 3;
	else if (r4.isOn(hitpoint)) return 4;
	else if (r5.isOn(hitpoint)) return 5;
	else if (r6.isOn(hitpoint)) return 6;
	else return -1;*/
}

RecPlane Hexahedron::getRecPlane(int i) const
{
	if (i == 1) return r1;
	else if (i == 2) return r2;
	else if (i == 3) return r3;
	else if (i == 4) return r4;
	else if (i == 5) return r5;
	else if (i == 6) return r6;
	else return RecPlane();
}

bool Hexahedron::isOn(const Vec &P) const
{
	bool result = false;
	for (int i = 1; i <= 6;i++)
	{
		result = result || getRecPlane(i).isOn(P);
	}
	return result;
}
