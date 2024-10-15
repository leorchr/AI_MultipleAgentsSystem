#include "Agent.h"
#include "Node.h"
#include "raylib.h"
#include "raymath.h"

Agent::Agent(Vector2 position) : position(position), speed(50), size(10), currentPathIndex(0) {}

Agent::~Agent() {}

void Agent::update(float dt) {
	if(!path.empty())
	{
		Vector2 direction = Vector2Subtract(path[currentPathIndex]->getCenterPosition(), position);
		Vector2 normDir = Vector2Normalize(direction);
		position = Vector2{position.x + normDir.x * (dt * speed),position.y + normDir.y * (dt * speed)};
		if(Vector2Length(Vector2Subtract(path[currentPathIndex]->getCenterPosition(), position)) < 10)
		{
			if(path.size() > currentPathIndex + 1) currentPathIndex++;
			else{
				path.clear();
				currentPathIndex = 0;
			}
		}
	}
}

void Agent::draw() {
	DrawCircleV(Vector2{position.x-(size/2), position.y-(size/2)}, 10, RED);
}

void Agent::setPath(std::vector<Node*> path) {
	this->path = path;
	currentPathIndex = 0;
}