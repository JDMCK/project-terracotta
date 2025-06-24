#ifndef EDITOR_H
#define EDITOR_H
#include "Tile.h"
#include "Canvas.h"

#define CANVAS_WIDTH 32
#define CANVAS_HEIGHT 32
#define CANVAS_CELL_SIZE 16

typedef enum EditorState {
    MENU,
    EDIT,
    EDIT_SAVE,
} EditorState;

typedef struct Editor {
    Camera2D camera;
    Canvas* canvas;
    Pallet* pallet;
    TextureAtlas* atlas;
    EditorState state;
    bool moveMode;
} Editor;

Editor* Editor_init();

void Editor_updateDraw(Editor* editor);

void Editor_free();

#endif //EDITOR_H
