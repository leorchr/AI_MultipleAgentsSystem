#include "Agent.h"
#include "Grid.h"
#include "raylib.h"
#include "Node.h"

const int speed = 30;
const int size = 10;
const int separationDist = 20;
const float separationFactor = 0.3f;
const int alignementDist = 50;
const float alignementFactor = 0.1f;

Agent* agent = new Agent(Vector2{ 50,50 }, separationDist, alignementDist, separationFactor, alignementFactor, speed, size);
Agent* agent2 = new Agent(Vector2{ 60,60 }, separationDist, alignementDist, separationFactor, alignementFactor, speed, size);
Agent* agent3 = new Agent(Vector2{ 40,40 }, separationDist, alignementDist, separationFactor, alignementFactor, speed, size);
std::vector<Agent*> agents = { agent, agent2, agent3 };

Grid* grid = new Grid(agents);

int main() {
    

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pathfinding");
    SetTargetFPS(60);
    //ToggleFullscreen();

    for(auto agent:agents) agent->setAgents(agents);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        grid->update(dt);
	    for(auto agent : agents) agent->update(dt);
        BeginDrawing();
        ClearBackground(Color{ 255, 255, 255, 255 });
        grid->draw();
        for(auto agent : agents) agent->draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}