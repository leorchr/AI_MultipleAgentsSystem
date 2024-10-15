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

class Agent;

class Grid
{
public:
	Grid(std::vector<Agent*> agents);
	
	void update(float dt);
	void draw();
	Node& getNearestNode(const Vector2 pos);
	std::vector <Node*> doAStar(Vector2 startPos, Vector2 endPos);
	void setupAgentPath(Vector2 endPos);
	std::vector <Node*> makePath(Node* goalNode);
	std::vector <Node*> getChilds(Node* node);
	Vector2 getClampedMousePosition();

private:
	bool isDebugActive;
	enum DrawMode currentDrawMode;
	Node* nodes[horizontalSize][verticalSize];
	std::vector<Node*> path;
	std::vector <Agent*> agents;
	Agent* agent;
	Vector2 currentObjective;
};