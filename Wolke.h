#pragma once
class Wolke
{
public:
	Wolke(float nx, float ny, float nz, float nsx, float nsy, float nsz);
	void draw();
	~Wolke();

	float x;
	float y;
	float z;
	float sx;
	float sy;
	float sz;
};

