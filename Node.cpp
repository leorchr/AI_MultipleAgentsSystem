#include "Node.h"

Color getColorForType(Type type)
{
	switch(type)
	{
	case Type::Path:
		return WHITE;
	case Type::Obstacle:
		return obstaclesColor;
	case Type::StartPoint:
		return startPosColor;
	case Type::EndPoint:
		return endPosColor;
	}
	return WHITE;
}

Node::Node(Vector2 position,Type type) : g(0), h(0), f(0), parent(nullptr),
                               position(position), type(type) {}

Node::~Node(){}


void Node::draw()
{
	DrawRectangle(position.x * squareSize, position.y * squareSize, squareSize, squareSize, getColorForType(type));
}