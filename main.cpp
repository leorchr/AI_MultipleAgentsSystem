#include "City.h"
#include "raylib.h"

City* city = new City(3);

int main() {
    

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My first Raylib window!");
    SetTargetFPS(60);
    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        city->update(dt);
        city->draw();
        BeginDrawing();
        ClearBackground(DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}