#pragma once
#include "Grid.h"
#include <raylib.h>

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT= 720;

static constexpr Color obstaclesColor = Color{50,13,109, 155};
static constexpr Color startPosColor = Color{163,247,181, 255};
static constexpr Color endPosColor = Color{243,66,19, 155};
static constexpr int verticalSize = 40;
static constexpr int verticalRatioSize = WINDOW_HEIGHT/verticalSize;
static constexpr int horizontalSize = WINDOW_WIDTH/(WINDOW_HEIGHT/verticalSize);
static constexpr int squareSize = WINDOW_HEIGHT/verticalSize;	

enum Type
{
	Path,
	Obstacle,
	StartPoint,
	EndPoint
};

Color getColorForType(Type type);

class Node
{
public:
	Node(Vector2 position, Type type);
	~Node();
	void draw();

	Vector2 getPosition() const { return position; }
	Type getType() const { return type; }
	

private:
	int g,h,f;
	Node* parent;
	Vector2 position;
	Type type;
};

