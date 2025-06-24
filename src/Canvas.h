#ifndef CANVAS_H
#define CANVAS_H
#include "Tile.h"
#include "TextureAtlas.h"

#define CANVAS_HIGHLIGHT_THICKNESS 2
#define CANVAS_HIGHLIGHT_COLOR WHITE

typedef struct Canvas {
    // Tiles is an array of Tile structs
    Tile* tiles;
    size_t tilesPerRow;
    size_t tilesPerCol;
    size_t cellSize;
} Canvas;

int Canvas_setTile(Canvas* canvas, size_t row, size_t col, Tile tile);

int Canvas_setTileIndex(Canvas* canvas, size_t index, Tile tile);

Canvas* Canvas_init(size_t width, size_t height, size_t cellSize);

Tile* Canvas_getTile(Canvas* canvas, size_t row, size_t col);

Tile* Canvas_getTileAtCursor(Canvas* canvas, Camera2D* camera);

// TODO: Fill canvas with tiles from a file
int Canvas_populateFromFile(Canvas* canvas, const char* filename);

// TODO: Save canvas to a file
int Canvas_writeToFile(Canvas* canvas, const char* filename);

int Canvas_draw(Canvas* canvas, TextureAtlas* atlas);

int Canvas_drawBorder(Canvas* canvas);

int Canvas_drawTileHighlight(Canvas* canvas, Camera2D* camera);

void Canvas_free(Canvas* canvas);

#endif //CANVAS_H
