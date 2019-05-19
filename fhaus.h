#include "Farbe.h"
#pragma once
class FHaus
{
public:
	FHaus(float nx, float ny, float nz, int nsegx, int nstock, int nsegz, Farbe nouterCol, Farbe ninnerCol, float nscale);
	void draw();
	~FHaus();

	float x;
	float y;
	float z;
	int segmentex;
	int segmentez;
	int stockwerke;
	Farbe outerCol;
	Farbe innerCol;
	float scale;
};

