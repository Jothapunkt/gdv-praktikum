#pragma once
class Hochhaus
{
public:
	Hochhaus(float nx, float ny, float nz, float nsx, float nsy, float nsz);
	void draw();
	~Hochhaus();

	float x;
	float y;
	float z;
	float sx;
	float sy;
	float sz;
};

