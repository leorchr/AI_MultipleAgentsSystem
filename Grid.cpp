#include "Grid.h"
#include "Agent.h"
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
	}
	return WHITE;
}

Grid::Grid(std::vector<Agent*> agents) : isDebugActive(true), currentDrawMode(DrawMode::ObstacleNode), agents(
	                                         std::move(agents)), currentObjective(Vector2Zero())
{
	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			nodes[i][y] = new Node(Vector2{squareSize*i,squareSize*y}, Type::Empty);
		}
	}
}

void Grid::update(float dt)
{
	if(IsKeyPressed(KEY_W)) currentDrawMode = DrawMode::ObstacleNode;
	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		for(auto agent : agents) agent->setCanMove(false);
		Vector2 mousePos = getClampedMousePosition();
		Node& nodeTargeted = getNearestNode(mousePos);
		switch(currentDrawMode)
		{
		case DrawMode::ObstacleNode:
			nodeTargeted.setType(Type::Obstacle);
			if(currentObjective.x != 0 && currentObjective.y != 0) setupAgentPath(currentObjective);
			break;
		}
	}
	if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		for(auto agent : agents) agent->setCanMove(true);
	}
	if(IsKeyPressed(KEY_Q) && !isDebugActive) isDebugActive = true;
	else if(IsKeyPressed(KEY_Q) && isDebugActive) isDebugActive = false;
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		currentObjective = getClampedMousePosition();
		setupAgentPath(currentObjective);
	}
}

void Grid::draw()
{
	// Draw Nodes
	for(const auto& nodesB : nodes)
	{
		for(const auto& node : nodesB)
		{
			if(!isDebugActive && node->getType() == Type::Obstacle) node->draw();
			else if(isDebugActive) node->draw();
		}
	}
	
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
	
	// Draw Mouse
	Vector2 mousePos = getClampedMousePosition();
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

std::vector<Node*> Grid::doAStar(Vector2 startPos, Vector2 endPos)
{
	Node* goalNode = nullptr;

	// Initialize both open and closed list
	std::vector <Node*> openList = {};
	std::vector <Node*> closedList = {};

	// Add the start node
	Node* endNode = &getNearestNode(endPos);
	endNode->setType(Type::EndPoint);
	Node* startNode = &getNearestNode(startPos);
	startNode->setType(Type::StartPoint);
	openList.emplace_back(startNode);

	//Loop until find the end node
	while(!openList.empty())
	{
		//Init current node to the least F node
		Node* currentNode = nullptr;
		currentNode = openList[0];
		for(auto node : openList)
		{
			if (node->getF() < currentNode->getF()) currentNode = node;
		}
		
		closedList.emplace_back(currentNode);
		openList.erase(std::find(openList.begin(),openList.end(),currentNode));
		if(*currentNode == *endNode)
		{
			goalNode = currentNode;
			break;
		}
		std::vector<Node*> childNodes = getChilds(currentNode);
		
		for(auto children : childNodes)
		{
			Node* child = new Node(*children);
			//child est dans la liste fermée
			int distanceChildCurrent = (int)round(Vector2Distance(child->getCenterPosition(), currentNode->getCenterPosition()));
			int distanceChildEnd = (int)round(Vector2Distance(child->getCenterPosition(), endNode->getCenterPosition()));
			child->setG(currentNode->getG() + distanceChildCurrent);
			child->setH(distanceChildEnd);
			child->setF(child->getG() + child->getH());
			child->setParent(currentNode);

			//Child already in open list
			bool alreadyInsideList = false;
			for(auto openNode : openList)
			{
				if(*openNode == *child)
				{
					if(child->getF() <= openNode->getF())
					{
						openNode = child;
					}
					alreadyInsideList = true;
					break;
				}
			}
			if(!alreadyInsideList) openList.push_back(child);
		}
	}
	
	std::vector<Node*> path = makePath(goalNode);
	return path;
}

void Grid::setupAgentPath(Vector2 endPos)
{
	for(auto node : path)
	{
		for(int i = 0; i < horizontalSize; i++)
		{
			for(int y = 0; y < verticalSize; y++)
			{
				if(*nodes[i][y] == *node)
				{
					if(nodes[i][y]->getType() == Type::Obstacle) continue;
					nodes[i][y]->setType(Type::Empty);
				}
			}
		}
		node->setType(Type::Empty);
	}
	path = doAStar(agents[0]->getPosition(), endPos);
	for(auto agent : agents) agent->setPath(path);
}

std::vector<Node*> Grid::makePath(Node* goalNode)
{
	std::vector<Node*> path;
	while (goalNode != nullptr)
	{
		path.push_back(goalNode);
		goalNode = goalNode->getParent();
	}
	std::reverse(path.begin(), path.end());

	for(auto node : path)
	{
		for(int i = 0; i < horizontalSize; i++)
		{
			for(int y = 0; y < verticalSize; y++)
			{
				if(*nodes[i][y] == *node)
				{
					nodes[i][y]->setType(Type::Path);
				}
			}
		}
		node->setType(Type::Path);
	}
	path[0]->setType(Type::StartPoint);
	return path;
}

std::vector<Node*> Grid::getChilds(Node* node)
{
	for(int i = 0; i < horizontalSize; i++)
	{
		for(int y = 0; y < verticalSize; y++)
		{
			if(*nodes[i][y] == *node)
			{
				std::vector<Node*> out;
				if(i-1 >= 0)
				{
					if(nodes[i-1][y]->getType() != Type::Obstacle) out.push_back(nodes[i-1][y]);
				}
				if(i+1 < horizontalSize && nodes[i-1][y]->getType() != Type::Obstacle)
				{
					if(nodes[i+1][y]->getType() != Type::Obstacle) out.push_back(nodes[i+1][y]);
				}
				if(y-1 >= 0)
				{
					if(nodes[i][y-1]->getType() != Type::Obstacle) out.push_back(nodes[i][y-1]);
				}
				if(y+1 < verticalSize)
				{
					if(nodes[i][y+1]->getType() != Type::Obstacle) out.push_back(nodes[i][y+1]);
				}
				
				if(y-1 >=0 && i-1 >=0)
				{
					if(nodes[i-1][y-1]->getType() != Type::Obstacle) out.push_back(nodes[i-1][y-1]);
				}
				if(i-1 >= 0 && y+1 < verticalSize)
				{
					if(nodes[i-1][y+1]->getType() != Type::Obstacle)out.push_back(nodes[i-1][y+1]);
				}
				if(i+1 < horizontalSize && y-1 >= 0)
				{
					if(nodes[i+1][y-1]->getType() != Type::Obstacle) out.push_back(nodes[i+1][y-1]);
				}
				if(i+1 < horizontalSize && y+1 < verticalSize)
				{
					 if(nodes[i+1][y+1]->getType() != Type::Obstacle) out.push_back(nodes[i+1][y+1]);
				}
				
				return out;
			}
		}
	}
	return std::vector<Node*>{};
}

Vector2 Grid::getClampedMousePosition()
{
	Vector2 mousePos = GetMousePosition();
	if(mousePos.x < 0) mousePos.x = 10;
	if(mousePos.y < 0) mousePos.y = 10;
	if(mousePos.x > WINDOW_WIDTH) mousePos.x = WINDOW_WIDTH-10;
	if(mousePos.y > WINDOW_HEIGHT) mousePos.y = WINDOW_HEIGHT-10;
	return mousePos;
}