#include <PCH.hpp>

int main() {
    InitWindow(800, 600, "kodelib engine example");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}