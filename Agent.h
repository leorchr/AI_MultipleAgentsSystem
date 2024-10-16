#pragma once
#include <raylib.h>
#include <vector>

class Node;
static constexpr Color agentColor = Color{255,102,99, 255};

class Agent
{
public:
	Agent(Vector2 position, int separationDist, int alignDist, float separationFactor, float alignFactor, int speed, int size);
	~Agent();
	void update(float dt);
	void draw();
	void setPath(std::vector<Node*> path);
	Vector2 getPosition() const { return position; }
	std::vector<Node*> getPath() const { return path; }
	void setCanMove(bool canMove);
	void setCurrentPathIndex(int index);
	void setAgents(std::vector<Agent*> agents);
	Vector2 separate(Agent* other);
	Vector2 align(Agent* other);
	int getId() const { return id; }
	Vector2 getcurrentDirection() const { return currentDirection; }
	
private:
	Vector2 position;
	Vector2 currentDirection;
	int separationDist;
	int alignDist;
	float separationFactor;
	float alignFactor;
	
	int speed;
	int size;
	
	bool canMove;
	int currentPathIndex;
	std::vector<Node*> path;
	std::vector<Agent*> agents;
	static int agentsCreated;
	int id;
};
