#include "Node.h"

Color getColorForType(Type type)
{
	switch(type)
	{
	case Type::Empty:
		return WHITE;
	case Type::Obstacle:
		return obstaclesColor;
	case Type::StartPoint:
		return startPosColor;
	case Type::EndPoint:
		return endPosColor;
	case Type::Path:
		return pathColor;
	}
	return WHITE;
}

Node::Node(Vector2 position,Type type) : g(0), h(0), f(0), parent(nullptr),
                               position(position), type(type) {}

Node::Node() : g(0), h(0), f(0), parent(nullptr),
				position(Vector2{0,0}), type(Type::Empty) {}

bool Node::operator==(const Node& other) const
{
	return position.x == other.position.x && position.y == other.position.y;
}

Node::~Node() {}

void Node::draw()
{
	DrawRectangle(position.x, position.y, squareSize, squareSize, getColorForType(type));
}

void Node::setType(Type type)
{
	this->type = type;
}

void Node::setF(int f)
{
	this->f = f;
}

void Node::setG(int g)
{
	this->g = g;
}

void Node::setH(int h)
{
	this->h = h;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}