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
	
	Vector2 separate(Agent* other);
	Vector2 align(Agent* other);
	void setPath(std::vector<Node*> path);
	void setCurrentPathIndex(int index);
	std::vector<Node*> getPath() const { return path; }
	Vector2 getPosition() const { return position; }
	Vector2 getcurrentDirection() const { return currentDirection; }
	int getId() const { return id; }
	void setCanMove(bool canMove);
	void setAgents(std::vector<Agent*> agents);
	
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
