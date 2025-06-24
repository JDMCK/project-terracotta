#define RAYGUI_IMPLEMENTATION
#include "Editor.h"
#include "raylib.h"

int main() {
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Tiles");
    SetTargetFPS(60);

    Editor* editor = Editor_init();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Editor_updateDraw(editor);
    }

    CloseWindow();

    return 0;
}
