#include "Wolke.h"
#include <iostream>
#include <GL/freeglut.h>
#include "Wuerfel.h"


Wolke::Wolke(float nx, float ny, float nz, float nsx, float nsy, float nsz)
{
	std::cout << "Neue Wolke bei " << x << "/" << y << "/" << z << std::endl;
	x = nx;
	y = ny;
	z = nz;
	sx = nsx;
	sy = nsy;
	sz = nsz;
}

void Wolke::draw() {
	glTranslatef(x, y, z);
	glScalef(sx, sy, sz);
	Wuerfel(0.4);
}


Wolke::~Wolke()
{
}
