#include "Cube.h"
#include <iostream>
#include <GL/freeglut.h>
#include "Wuerfel.h"


Cube::Cube(float nx, float ny, float nz, Farbe c, float s)
{
	x = nx;
	y = ny;
	z = nz;

	size = s;
	display = true;
	col = c;
}


Cube::~Cube()
{
}

void Cube::draw() {
	if (!display) { return; }

	glTranslatef(x, y, z);
	glColor4f(col.r, col.g, col.b, col.a);

	Wuerfel(size);
}
