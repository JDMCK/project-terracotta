#include "Tile.h"
#include <stdlib.h>
#include "Editor.h"

#include <stdio.h>

#include "Canvas.h"
#include "raymath.h"
#include "utils.h"

Editor* Editor_init() {
    Editor* editor = malloc(sizeof(Editor));
    if (!editor) {
        log_error("Failed to allocate Editor");
        return NULL;
    }
    Camera2D camera = {0};
    camera.offset = (Vector2){(float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    camera.zoom = 1.f;
    editor->camera = camera;

    Canvas* canvas = Canvas_init(CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_CELL_SIZE);
    if (canvas == NULL) {
        log_error("Failed to allocate Canvas in Editor");
        return NULL;
    }
    editor->canvas = canvas;

    editor->atlas = TextureAtlas_init("../resources/basictiles.png", CANVAS_CELL_SIZE, CANVAS_CELL_SIZE, 16);

    Pallet* pallet = Pallet_init(8, 2, CANVAS_CELL_SIZE, editor->atlas);
    if (pallet == NULL) {
        log_error("Failed to allocate Pallet in Editor");
        return NULL;
    }
    editor->pallet = pallet;

    editor->state = EDIT;

    editor->moveMode = false;

    return editor;
};

void Editor_updateDraw(Editor* editor) {
    // Handle input ---------------------------------------------
    editor->moveMode = IsKeyDown(KEY_SPACE);

    const float scrollMovement = GetMouseWheelMove();
    if (scrollMovement) {
        const float scrollSensitivity = 0.1f;
        editor->camera.zoom -= scrollMovement * scrollSensitivity;
        editor->camera.zoom = Clamp(editor->camera.zoom, 0.1f, 10);
    }
    if (editor->moveMode && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const Vector2 mouseDelta = GetMouseDelta();
        const Vector2 scaledMouseDelta = Vector2Scale(mouseDelta, 1 / editor->camera.zoom);
        const Vector2 moveVector = Vector2Subtract(editor->camera.target, scaledMouseDelta);
        editor->camera.target = moveVector;
    }
    if (!editor->moveMode && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Tile* palletTile = Pallet_getTileAtCursor(editor->pallet);
        Tile* canvasTile = Canvas_getTileAtCursor(editor->canvas, &editor->camera);
        if (palletTile == NULL && canvasTile != NULL && editor->pallet->selectedTile != NULL) {
            Tile_set(canvasTile, editor->pallet->selectedTile);
        } else if (palletTile != NULL) {
            Pallet_selectTile(editor->pallet, palletTile);
        }
    }
    if (!editor->moveMode && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Tile* canvasTile = Canvas_getTileAtCursor(editor->canvas, &editor->camera);
        if (canvasTile != NULL) {
            Tile_unset(canvasTile);
        }
    }

    BeginDrawing(); // ------------------------------------------
    ClearBackground(BLACK);
    BeginMode2D(editor->camera);

    Canvas_draw(editor->canvas, editor->atlas);
    Canvas_drawBorder(editor->canvas);
    if (!editor->moveMode) {
        Canvas_drawTileHighlight(editor->canvas, &editor->camera);
    }


    EndMode2D();
    // Draw overlay stuff here -----------------------------------
    Pallet_draw(editor->pallet, editor->atlas);
    if (!editor->moveMode) {
        Pallet_drawTileHighlight(editor->pallet);
    }


    // if (GuiButton((Rectangle){24, 24, 120, 30}, "#191#Show Message")) showMessageBox = true;
    //
    // if (showMessageBox) {
    //     int result = GuiMessageBox((Rectangle){85, 70, 250, 100},
    //                                "#191#Message Box", "Hi! This is a message!", "Nice;Cool");
    //     if (result >= 0) showMessageBox = false;
    // }

    EndDrawing(); // -----------------------------------------------
}
