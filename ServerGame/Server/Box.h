#pragma once
class Box {
public:
	float x, y, vx, vy;
	float width, height;

	Box() {
		x = y = vx = vy = width = height = 0;
	}

	Box(float x, float y, float vx, float vy, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
		this->width = width;
		this->height = height;
	}
};
