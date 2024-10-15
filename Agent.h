﻿#pragma once
#include <raylib.h>
#include <vector>

static constexpr int speed = 100;

class Node;

class Agent
{
public:
	Agent(Vector2 position);
	~Agent();
	void update(float dt);
	void draw();
	void setPath(std::vector<Node*> path);
	Vector2 getPosition() const { return position; }
	std::vector<Node*> getPath() const { return path; }
	void setCanMove(bool canMove);
	void setAgents(std::vector<Agent*> agents);
	Vector2 separate(Agent* other);
	Vector2 align(Agent* other);
	int getId() const { return id; }
	Vector2 getVelocity() const { return velocity; }
	
private:
	Vector2 position;
	int speed;
	int size;
	int currentPathIndex;
	bool canMove;
	std::vector<Node*> path;
	std::vector<Agent*> agents;
	static int agentsCreated;
	int id;
	Vector2 velocity;

	const int separationDist = 10;
	const int alignDist = 50;
};
