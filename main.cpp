#include "Grid.h"
#include "raylib.h"
#include "Node.h"

Grid* grid = new Grid();

int main() {
    

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pathfinding");
    SetTargetFPS(60);
    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        grid->update(dt);
        grid->draw();
        BeginDrawing();
        ClearBackground(Color{ 200, 200, 200, 255 });
        EndDrawing();
    }

    CloseWindow();
    return 0;
}