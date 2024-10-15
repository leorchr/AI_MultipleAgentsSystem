#include "Agent.h"
#include "Grid.h"
#include "raylib.h"
#include "Node.h"

Agent* agent = new Agent(Vector2{ 50,50 });
Grid* grid = new Grid(agent);

int main() {
    

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pathfinding");
    SetTargetFPS(60);
    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        grid->update(dt);
        agent->update(dt);
        BeginDrawing();
        ClearBackground(Color{ 255, 255, 255, 255 });
        grid->draw();
        agent->draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}