#ifndef INTERSECTRESULT_H_INCLUDED
#define INTERSECTRESULT_H_INCLUDED
#include "Geometry.h"

class Geometry;

struct IntersecResult
{
	double distance;
	bool isHit;
	Vec position;
	Vec normal;
	Geometry *_object;

	IntersecResult(){ _object = NULL; isHit = false; }
	
	void copy(IntersecResult &in)
	{
		in.distance = distance;
		in.isHit = isHit;
		in.position = position;
		in.normal = normal;
		in._object = _object;
	}
	static inline IntersecResult noHit() { return IntersecResult(); }
};


#endif // INTERSECTRESULT_H_INCLUDED