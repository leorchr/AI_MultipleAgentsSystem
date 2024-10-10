#include "Grid.h"
#include "Node.h"
#include <raylib.h>

Color getColorForDrawMode(DrawMode drawMode)
{
	switch(drawMode)
	{
	case DrawMode::obstacleNode:
		return obstaclesColor;
	case DrawMode::startNode:
		return startPosColor;
	case DrawMode::endNode:
		return endPosColor;
	}
	return WHITE;
}

Grid::Grid() : nodes(std::vector<Node*>())
{
	currentDrawMode = DrawMode::obstacleNode;
	isDebugActive = true;
}

void Grid::update(float dt)
{
	if(IsKeyPressed(KEY_Q)) currentDrawMode = DrawMode::startNode;
	if(IsKeyPressed(KEY_E)) currentDrawMode = DrawMode::endNode;
	if(IsKeyPressed(KEY_W)) currentDrawMode = DrawMode::obstacleNode;
	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = GetMousePosition();
		Vector2 posTargeted = getNearestPosition(mousePos);
		bool canDrawStart = true;
		bool canDrawEnd = true;
		switch(currentDrawMode)
		{
		case DrawMode::obstacleNode:
			addNodeToDraw(posTargeted);
			break;
		case DrawMode::startNode:
			for(auto node : nodes)
			{
				if(node->getType() == Type::StartPoint)
				{
					canDrawStart = false;
					break;
				}
			}
			if(canDrawStart) addNodeToDraw(posTargeted);
			break;
		case DrawMode::endNode:
			for(auto node : nodes)
			{
				if(node->getType() == Type::EndPoint)
				{
					canDrawEnd = false;
					break;
				}
			}
			if(canDrawEnd) addNodeToDraw(posTargeted);
			break;
		}
	}
	if(IsKeyPressed(KEY_D) && !isDebugActive) isDebugActive = true;
	else if(IsKeyPressed(KEY_D) && isDebugActive) isDebugActive = false;
}

void Grid::draw()
{
	// Draw Grid
	if(isDebugActive)
	{
		for(int i = 1; i < verticalSize; i++)
		{
			DrawLine(0,squareSize * i,WINDOW_WIDTH, squareSize * i, borderColor);
		}
		for (int y= 1; y < horizontalSize; y++)
		{
			DrawLine(squareSize * y,0,squareSize * y, WINDOW_HEIGHT, borderColor);
		}
	}

	for(auto node : nodes)
	{
		node->draw();
	}

	// Draw Mouse
	Vector2 mousePos = GetMousePosition();
	DrawCircle(mousePos.x, mousePos.y,5,getColorForDrawMode(currentDrawMode));
}

Vector2 Grid::getNearestPosition(Vector2 pos)
{
	float squarePosX = 0.0f;
	float squarePosY = 0.0f;
	for(int i = 0; i < horizontalSize + 1; i++)
	{
		if(squareSize * i > pos.x)
		{
			squarePosX = i-1;
			break;
		}
	}
	for(int y = 0; y < verticalSize + 1; y++)
	{
		if(squareSize * y > pos.y)
		{
			squarePosY = y-1;
			break;
		}
	}
	Vector2 posTargeted = {squarePosX,squarePosY};
	return posTargeted;
}

void Grid::addNodeToDraw(Vector2 position)
{
	for(auto node : nodes)
	{
		if(node->getPosition().x == position.x && node->getPosition().y == position.y) return;
	}
	
	switch(currentDrawMode)
	{
	case DrawMode::obstacleNode:
			nodes.emplace_back(new Node(position, Type::Obstacle));
			break;
		case DrawMode::startNode:
			nodes.emplace_back(new Node(position, Type::StartPoint));
			break;
		case DrawMode::endNode:
			nodes.emplace_back(new Node(position, Type::EndPoint));
			break;
	}
}

std::vector<Vector2> Grid::doAStar()
{
	std::vector <Node*> openList = {};
	std::vector <Node*> closedList = {};

	for(auto node : nodes)
	{
		if(node->getType() == Type::StartPoint) openList.emplace_back();
	}

	bool isFound = false;

	Node* currentNode = openList[0];
	
	while(openList.size()!=0)
	{
		for(auto list : openList)
		{
			
		}
		closedList.emplace_back(currentNode);
		closedList.emplace_back()
	}
}
