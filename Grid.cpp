﻿#include "Grid.h"
#include <chrono>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

Color getColorForDrawMode(DrawMode drawMode)
{
	switch(drawMode)
	{
	case DrawMode::ObstacleNode:
		return obstaclesColor;
	case DrawMode::StartNode:
		return startPosColor;
	case DrawMode::EndNode:
		return endPosColor;
	}
	return WHITE;
}

Grid::Grid() : isDebugActive(true), currentDrawMode(DrawMode::ObstacleNode), canDrawStart(true), canDrawEnd(true)
{
	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			nodes[i][y] = new Node(Vector2{squareSize*i,squareSize*y}, Type::Path);
		}
	}
}

void Grid::update(float dt)
{
	if(IsKeyPressed(KEY_Q)) currentDrawMode = DrawMode::StartNode;
	if(IsKeyPressed(KEY_E)) currentDrawMode = DrawMode::EndNode;
	if(IsKeyPressed(KEY_W)) currentDrawMode = DrawMode::ObstacleNode;
	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = GetMousePosition();
		Node& nodeTargeted = getNearestNode(mousePos);
		switch(currentDrawMode)
		{
		case DrawMode::ObstacleNode:
			if(nodeTargeted.getType() == Type::Path) nodeTargeted.setType(Type::Obstacle);
			break;
		case DrawMode::StartNode:
			if(canDrawStart && nodeTargeted.getType() == Type::Path) 
			{
				nodeTargeted.setType(Type::StartPoint);
				canDrawStart = false;
			}
			break;
		case DrawMode::EndNode:
			if(canDrawEnd && nodeTargeted.getType() == Type::Path) 
			{
				nodeTargeted.setType(Type::EndPoint);
				canDrawEnd = false;
			}
			break;
		}
	}
	if(IsKeyPressed(KEY_D) && !isDebugActive) isDebugActive = true;
	else if(IsKeyPressed(KEY_D) && isDebugActive) isDebugActive = false;
	if(IsKeyDown(KEY_SPACE) && !canDrawStart && !canDrawEnd) doAStar();
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

	for(const auto& nodesB : nodes)
	{
		for(const auto& node : nodesB)
		{
			node->draw();
		}
	}
	
	// Draw Mouse
	Vector2 mousePos = GetMousePosition();
	DrawCircle(mousePos.x, mousePos.y,5,getColorForDrawMode(currentDrawMode));
}

Node& Grid::getNearestNode(Vector2 pos)
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
	Vector2 outPos = {squarePosX*squareSize,squarePosY*squareSize};
	Node* nodeTargeted = nullptr;

	for(const auto& nodesX : nodes)
	{
		if(nodesX[0]->getPosition().x == outPos.x)
		{
			for(const auto& node : nodesX)
			{
				if(node->getPosition().y == outPos.y)
				{
					nodeTargeted = node;
					break;
				}
			}
		}
	}
	return *nodeTargeted;
}

std::vector<Node*> Grid::doAStar()
{
	Node* goalNode = nullptr;
	std::vector<Node*> path;
	std::vector <Node*> openList = {};
	std::vector <Node*> closedList = {};

	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			if(nodes[i][y]->getType() == Type::StartPoint) openList.emplace_back(nodes[i][y]);
		}
	}

	
	while(openList.size()!=0)
	{
		Node* currentNode = nullptr;
		for(auto node : openList)
		{
			if(currentNode == nullptr) currentNode = node;
			else if (node->getF() < currentNode->getF()) currentNode = node;
		}
		
		closedList.emplace_back(currentNode);
		openList.erase(std::find(openList.begin(),openList.end(),currentNode));
		if(currentNode->getType() == Type::EndPoint)
		{
			goalNode = currentNode;
			break;
		}
		std::vector<Node*> childNodes = getChilds(currentNode);
		
		for(auto childrens : childNodes)
		{
			Node child = Node(Vector2{childrens->getPosition().x, childrens->getPosition().y}, childrens->getType());
			if(std::find(closedList.begin(), closedList.end(), &child) != closedList.end()) continue;

			int distanceChildCurrent = (int)round(Vector2Distance(child.getCenterPosition(), currentNode->getCenterPosition()));
			int distanceChildEnd = (int)round(Vector2Distance(child.getCenterPosition(), getEndNode().getCenterPosition()));
			child.setG(currentNode->getG() + distanceChildCurrent);
			child.setH(distanceChildEnd);
			child.setF(child.getG() + child.getH());
			child.setParent(currentNode);

			auto it = std::find(openList.begin(), openList.end(), &child);
			if (it != openList.end())
			{
				Node* existingNode = *it;
				if (child.getG() > existingNode->getG())
				{
					continue;
				}
			}
			openList.push_back(&child);
		}

	}

	while (goalNode != nullptr) // Remonte jusqu'à ce que tu atteignes le nœud de départ
	{
		path.push_back(goalNode);
		goalNode = goalNode->getParent(); // Passe au nœud parent
	}

	std::reverse(path.begin(), path.end());
	
	return path;
}

std::vector<Node*> Grid::getChilds(Node* node)
{
	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			if(nodes[i][y] == node) 
			{
				std::vector<Node*> out;
				if(i-1 >= 0) out.push_back(nodes[i-1][y]);
				if(i+1 < horizontalSize) out.push_back(nodes[i+1][y]);
				if(y-1 >= 0) out.push_back(nodes[i][y-1]);
				if(y+1 < verticalSize) out.push_back(nodes[i][y+1]);
				return out;
			}
		}
	}
	return std::vector<Node*>{};
}

Node& Grid::getEndNode()
{
	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			if(nodes[i][y]->getType() == Type::StartPoint) return *nodes[i][y];
		}
	}
	return *nodes[0][0];
}