#include "Agent.h"
#include "Node.h"
#include "raylib.h"
#include "raymath.h"

int Agent::agentsCreated = 0;

Agent::Agent(Vector2 position, int separationDist, int alignDist, float separationFactor, float alignFactor, int speed, int size) :
	position(position), currentDirection(Vector2Zero()), separationDist(separationDist), alignDist(alignDist), separationFactor(separationFactor), alignFactor(alignFactor),
	speed(speed), size(size), canMove(true), currentPathIndex(0), id(0)
{
	id = agentsCreated;
	agentsCreated++;
	path = {};
	agents = {};
}

Agent::~Agent() {}

void Agent::update(float dt) {
	Vector2 pathDir = Vector2Zero();
	
	Vector2 separationValue = Vector2Zero();
	int separationSum = 0;
	
	Vector2 alignementValue = Vector2Zero();
	int alignementSum = 0;

	for (auto agent:agents)
	{
		if(agent->getId() == this->id) continue;
		
		Vector2 separationTemp = separate(agent);
		if(separationTemp.x != Vector2Zero().x && separationTemp.y != Vector2Zero().y)
		{
			separationValue = Vector2Add(separationValue, separationTemp);
			separationSum++;
		}
		
		Vector2 alignementTemp = align(agent);
		if(alignementTemp.x != Vector2Zero().x && alignementTemp.y != Vector2Zero().y)
		{
			alignementValue = Vector2Add(alignementValue, alignementTemp);
			alignementSum++;
		}
	}
	if(separationSum != 0)
	{
		separationValue.x /= separationSum;
		separationValue.y /= separationSum;
	}
	if(alignementSum != 0)
	{
		alignementValue.x /= alignementSum;
		alignementValue.y /= alignementSum;
	}
	
	Vector2 separation = separationValue;
	Vector2 alignement = alignementValue;
	
	if(canMove)
	{
		if(!path.empty())
		{
			Vector2 direction = Vector2Subtract(path[currentPathIndex]->getCenterPosition(), position);
			pathDir = Vector2Normalize(direction);
			if(Vector2Length(Vector2Subtract(path[currentPathIndex]->getCenterPosition(), position)) < 10)
			{
				if(path.size() > currentPathIndex + 1)
				{
					currentPathIndex++;
					for(auto agent : agents) agent->setCurrentPathIndex(currentPathIndex);
				}
				else{
					path.clear();
					currentPathIndex = 0;
				}
			}
		}
	}

	Vector2 dir = Vector2Zero();
	separation.x *= separationFactor;
	separation.y *= separationFactor;
	dir=Vector2Add(dir, separation);
	alignement.x *= alignFactor;
	alignement.y *= alignFactor;
	dir=Vector2Add(dir, alignement);
	dir=Vector2Add(dir, pathDir);
	Vector2Normalize(dir);
	Vector2 newPosition = Vector2{position.x + dir.x * (dt * speed),position.y + dir.y * (dt * speed)};
	position = newPosition;
}

void Agent::draw() {
	DrawCircleV(Vector2{position.x-(size/2), position.y-(size/2)}, size, agentColor);
}

void Agent::setPath(std::vector<Node*> path) {
	this->path = path;
	currentPathIndex = 0;
}

void Agent::setCanMove(bool canMove)
{
	this->canMove = canMove;
}

void Agent::setCurrentPathIndex(int index)
{
	if(index>=0 && index < path.size()) currentPathIndex = index;
}

void Agent::setAgents(std::vector<Agent*> agents)
{
	this->agents = agents;
}

Vector2 Agent::separate(Agent* other)
{
	Vector2 posBoid = other->getPosition();
	Vector2 posSelf = position;
	Vector2 distVector2 = Vector2Subtract(posSelf,posBoid);
		
	float dist = Vector2Length(distVector2);
	if(dist < separationDist)
	{
		Vector2Normalize(distVector2);
		return distVector2;
	}
	else return Vector2Zero();
}

Vector2 Agent::align(Agent* other)
{
	Vector2 posBoid = other->getPosition();
	Vector2 posSelf = position;
	Vector2 distVector2 = Vector2Subtract(posSelf,posBoid);
				
	float dist = Vector2Length(distVector2);
	if(dist < alignDist)
	{
		return other->getcurrentDirection();
	}
	else return Vector2Zero();
}