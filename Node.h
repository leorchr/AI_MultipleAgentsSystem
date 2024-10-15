#pragma once
#include <raylib.h>

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT= 720;

static constexpr Color obstaclesColor = Color{50,13,109, 155};
static constexpr Color startPosColor = Color{163,247,181, 255};
static constexpr Color endPosColor = Color{243,66,19, 155};
static constexpr Color pathColor = Color{147,129,255, 155};
static constexpr int verticalSize = 40;
static constexpr int verticalRatioSize = WINDOW_HEIGHT/verticalSize;
static constexpr int horizontalSize = WINDOW_WIDTH/(WINDOW_HEIGHT/verticalSize);
static constexpr float squareSize = WINDOW_HEIGHT/verticalSize;


enum Type
{
	Empty,
	Obstacle,
	StartPoint,
	EndPoint,
	Path
};

Color getColorForType(Type type);

class Node
{
public:
	Node(Vector2 position, Type type);
	Node();
	Node(const Node& other);
	bool operator==(const Node& other) const;
	~Node();
	void draw();

	void setType (Type type);
	Vector2 getPosition() const { return position; }
	Vector2 getCenterPosition() const { return Vector2{position.x + squareSize, position.y + squareSize}; }
	Type getType() const { return type; }
	Node* getParent() const { return parent; }
	int getF() const { return f; }
	int getG() const { return g; }
	int getH() const { return h; }
	void setF(int f);
	void setG(int g);
	void setH(int h);
	void setParent(Node* parent);
	

private:
	int g,h,f;
	Node* parent;
	Vector2 position;
	Type type;
	static int nodesCreated;
	int id;
};

