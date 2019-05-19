#pragma once
#include "Farbe.h"
class Cube
{
public:
	Cube(float nx, float ny, float nz, Farbe c, float s);
	~Cube();

	Farbe col;
	float x;
	float y;
	float z;

	float size;

	bool display;

	void draw();
};

