#include "Hochhaus.h"
#include <iostream>
#include <GL/freeglut.h>
#include "Wuerfel.h"


Hochhaus::Hochhaus(float nx, float ny, float nz, float nsx, float nsy, float nsz)
{
	std::cout << "Neues Hochhaus bei " << x << "/" << y << "/" << z << std::endl;
	x = nx;
	y = ny;
	z = nz;
	sx = nsx;
	sy = nsy;
	sz = nsz;
}

void Hochhaus::draw() {
	glTranslatef(x, y, z);
	glScalef(sx, sy, sz);
	Wuerfel(0.4);
}


Hochhaus::~Hochhaus()
{
}
