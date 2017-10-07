#include <stdlib.h>
#include <stdio.h>
#include "Union.h"
#include "Sphere.h"
#include "Plane.h"
#include "CylinderInf.h"
#include "Cylinder.h"
#include "Hexahedron.h"

#define WIDTH 1024
#define HEIGHT 768
//#define LIGHT Vec(0.1, 0.1, 0.1)


Vec radiance(Geometry *scene, Ray &ray, int depth)
{
	IntersecResult result = scene->isIntersected(ray);	
	if (result._object != NULL)
	{
		double t = result.distance;
		const Geometry *obj = result._object;
		int ref = obj->ref;
		Vec x = result.position; // hit point
		Vec f = obj->color;

		// get the max factor of color RGB as max refl, RGB is in 0-1
		double p = f.x > f.y && f.x > f.z ?
			f.x : f.y > f.z ?
			f.y : f.z; // max refl 		

		if (++depth > 5)  // max reflection times is 5
		{
			if (erand48() < p) // if lucky, change color do another time
				f = f*(1 / p);
			else
				return obj->emit; //if not lucky, use its emission color 
		}
		

		Ray reflectionLight = obj->getReflection(ray, x);
		if (obj->ref == 2)
		{
			double Re = 0;
			Ray refractionLight = obj->getRefraction(ray, x, Re);
			
			double Tr = 1 - Re,
				P = .25 + .5*Re,
				RP = Re / P,
				TP = Tr / (1 - P);

			if (depth > 2)
			{
				if (erand48() < P)
				{
					return obj->emit + f.mult(radiance(scene, reflectionLight, depth) * RP);
				}
				else
				{
					return obj->emit + f.mult(radiance(scene, refractionLight, depth) * TP);
				}
			}
			else
			{
				return obj->emit
					+ f.mult(radiance(scene, reflectionLight, depth)*Re + radiance(scene, refractionLight, depth)*Tr);
			}			
		}
		else
		{
			return obj->emit
				+ f.mult(radiance(scene, reflectionLight, depth));
		}
	}
	else
	{
		return Vec(); // if miss, return black
	}
}

// DIFF: 0; SPE: 1; REFR: 2

int main()
{
	int samps = 4;
	Ray cam(Vec(60, 52, 300.6), Vec(0, -0.042612, -1).norm()); // cam pos, dir 
	Vec cx = Vec(WIDTH*.5135 / HEIGHT), cy = (cx%cam.d).norm()*.5135, r, *c = new Vec[WIDTH*HEIGHT];
	
	Cylinder *cylinder1 = new Cylinder(Vec(50, 50, 80), Vec(40, 30, 60), 10, Vec(), Vec(1, 1, 1)*.999, 2);
	Hexahedron *hexa = new Hexahedron(Vec(60, 20, 80), Vec(80, 20, 100), Vec(-0.4, -0.3, 1), Vec(85, 45, 85), Vec(), Vec(0.82, 0.13, 0.82), 0);
	Plane *left = new Plane(Vec(0, 0, 0), Vec(1, 0, 0), Vec(), Vec(.75, .25, .25), 0);
	Plane *botm = new Plane(Vec(0,0,0), Vec(0, 1, 0), Vec(), Vec(.75, .75, .75), 0);
	Plane *bck = new Plane(Vec(0, 0, -10), Vec(0, 0, 1), Vec(), Vec(0.999, 0.999, 0), 0);
	Plane *top = new Plane(Vec(0,81,0), Vec(0, 1, 0), Vec(), Vec(.75, .75, .75), 0);
	Plane *right = new Plane(Vec(120, 0, 0), Vec(-1, 0, 0), Vec(), Vec(.25, .25, .75), 0);	
	Sphere *sphere7 = new Sphere(16.5, Vec(27	, 16.5, 100), Vec(), Vec(1, 1, 1)*.999, 1); // mirr
	Sphere *sphere8 = new Sphere(14, Vec(90, 14, 80), Vec(), Vec(0.999, 0.999, 0.999), 2); // glas
	Sphere *sTop = new Sphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), 0);
	Sphere *sphere9 = new Sphere(8, Vec(45, 8, 120), Vec(), Vec(0.5, 0.2, 0.0), 2); // glas
	Sphere *light = new Sphere(600, Vec(60, 681.6 - .27, 80.6), Vec(12, 12, 12), Vec(), 0); //Lite
	Sphere *lightl = new Sphere(2, Vec(2, 50, 50), Vec(100, 100, 100), Vec(), 0);
	Sphere *lightr = new Sphere(2, Vec(118, 50, 50), Vec(100, 100, 100), Vec(), 0);
	
	Union scence;

	scence.push(lightl);
	scence.push(lightr);
	scence.push(cylinder1);
	scence.push(hexa);
	scence.push(sphere9);
	scence.push(right);
	scence.push(bck); 
	scence.push(left);
	scence.push(botm);	
	scence.push(sphere7); 
	scence.push(sphere8); 
	scence.push(light);
	scence.push(sTop);
	Ray aray;

#pragma omp parallel for schedule(dynamic, 1) private(r)  
	for (int y = 0; y < HEIGHT; y++)
	{
		fprintf(stderr, "\rRendering (%d spp) %5.2f%%", samps * 4, 100.*y / (HEIGHT - 1));
		for (unsigned short x = 0; x < WIDTH; x++)
		{
			for (int sy = 0, i = (HEIGHT - y - 1)*WIDTH + x; sy < 2; sy++)
			{
				for (int sx = 0; sx < 2; sx++, r = Vec())
				{
					for (int s = 0; s < samps; s++)
					{
						double r1 = 2 * erand48(), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						double r2 = 2 * erand48(), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
						Vec d = cx*(((sx + .5 + dx) / 2 + x) / WIDTH - .5) +
							cy*(((sy + .5 + dy) / 2 + y) / HEIGHT - .5) + cam.d;
						aray = Ray(cam.o + d * 140, d.norm());
						r = r + radiance(&scence, aray, 0)*(1. / samps);
					}
					c[i] = c[i] + Vec(clamp(r.x), clamp(r.y), clamp(r.z))*.25;
				}
			}
		}
	}

	unsigned char *picData = (unsigned char *)malloc(WIDTH*HEIGHT * 3);

	for (int w = 0; w < WIDTH; w++)
	{
		for (int h = 0; h < HEIGHT; h++)
		{
			int index = h*WIDTH + w;
			picData[3 * index] = (unsigned char)(toInt(c[index].x));
			picData[3 * index + 1] = (unsigned char)(toInt(c[index].y));
			picData[3 * index + 2] = (unsigned char)(toInt(c[index].z));
		}
	}

	savebmp(picData, "image.bmp", WIDTH, HEIGHT);
	delete[] picData;

	return 0;
}