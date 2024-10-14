#pragma once
#include "Node.h"
#include <raylib.h>
#include <vector>

static constexpr auto borderColor = WHITE;

enum DrawMode
{
	StartNode,
	EndNode,
	ObstacleNode
};

Color getColorForDrawMode(DrawMode drawMode);

class Grid
{
public:
	Grid();
	
	void update(float dt);
	void draw();
	Node& getNearestNode(const Vector2 pos);
	std::vector <Node*> doAStar();
	std::vector <Node*> getChilds(Node* node);
	Node& getEndNode();

private:
	bool isDebugActive;
	enum DrawMode currentDrawMode;
	Node* nodes[horizontalSize][verticalSize];
	bool canDrawStart;
	bool canDrawEnd;
};