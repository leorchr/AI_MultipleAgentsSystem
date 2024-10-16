#include "Agent.h"
#include "Grid.h"
#include "raylib.h"
#include "Node.h"

const int speed = 60;
const int size = 10;
const int separationDist = 20;
const float separationFactor = 0.05f;
const int alignementDist = 30;
const float alignementFactor = 0.5f;
const int agentsNumber = 5;



int main() {

    std::vector<Agent*> agents = {};
    for(int i = 0; i < agentsNumber; i++)
    {
        Agent* agent = new Agent(Vector2{ 50,50 }, separationDist, alignementDist, separationFactor, alignementFactor, speed, size);
        agents.push_back(agent);
    }
    Grid* grid = new Grid(agents);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pathfinding");
    SetTargetFPS(60);
    //ToggleFullscreen();

    for(auto agent:agents) agent->setAgents(agents);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        grid->update(dt);
	    for(auto agent : agents) agent->update(dt);
        BeginDrawing();
        ClearBackground(Color{ 0, 39, 43, 255 });
        grid->draw();
        for(auto agent : agents) agent->draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}