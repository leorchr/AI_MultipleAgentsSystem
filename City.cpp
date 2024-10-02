#include "City.h"
#include <raylib.h>

City::City(int size) : size(size)
{
	
}

void City::update(float dt) {}

void City::draw()
{
	DrawCircle(0,0,50,WHITE);
	for(int i = 1; i < size; i++)
	{
		DrawLine(WINDOW_WIDTH/size * i,0,WINDOW_WIDTH/size * i, WINDOW_HEIGHT, WHITE);
		DrawLine(0,WINDOW_HEIGHT/size * i,WINDOW_WIDTH, WINDOW_HEIGHT/size * i, WHITE);
	}
}