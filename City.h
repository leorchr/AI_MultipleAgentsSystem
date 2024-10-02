#pragma once
#include <raylib.h>

const Color borderColor = Color{0,0,0,0};
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT= 800;

class City
{
public:
	City(int size);
	
	void update(float dt);
	void draw();

private:
	int size;
};
