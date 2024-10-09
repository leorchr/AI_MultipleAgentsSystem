#pragma once
#include <raylib.h>
#include <vector>

class Node;

const static auto borderColor = WHITE;

enum DrawMode
{
	startNode,
	endNode,
	obstacleNode
};

Color getColorForDrawMode(DrawMode drawMode);

class Grid
{
public:
	Grid();
	
	void update(float dt);
	void draw();

	Vector2 getNearestPosition(Vector2 pos);
	void addNodeToDraw(Vector2 pos);
	//std::vector <Vector2> doAStar();

private:
	bool isDebugActive;
	enum DrawMode currentDrawMode;
	std::vector<Node*> nodes;
};