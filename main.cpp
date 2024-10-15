#include "Agent.h"
#include "Grid.h"
#include "raylib.h"
#include "Node.h"

Agent* agent = new Agent(Vector2{ 50,50 });
Agent* agent2 = new Agent(Vector2{ 70,70 });
Agent* agent3 = new Agent(Vector2{ 1000,500 });

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