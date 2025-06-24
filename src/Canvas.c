#include "Canvas.h"
#include "Tile.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int Canvas_setTile(Canvas* canvas, size_t row, size_t col, Tile tile) {
    if (canvas == NULL) {
        return 1;
    }
    if (row >= canvas->tilesPerCol || col >= canvas->tilesPerRow) {
        return 1;
    }
    canvas->tiles[row * canvas->tilesPerRow + col] = tile;
    return 0;
}

int Canvas_setTileIndex(Canvas* canvas, size_t index, Tile tile) {
    if (canvas == NULL) {
        return 1;
    }
    size_t row = index / canvas->tilesPerRow;
    size_t col = index % canvas->tilesPerRow;
    Canvas_setTile(canvas, row, col, tile);
    return 0;
}

Canvas* Canvas_init(size_t width, size_t height, size_t cellSize) {
    Canvas* canvas = calloc(1, sizeof(Canvas));
    Tile* tiles = calloc(width * height, sizeof(Tile));
    if (canvas == NULL || tiles == NULL) {
        log_error("Failed to allocate memory for Canvas");
        return NULL;
    }
    canvas->tiles = tiles;
    canvas->tilesPerRow = width;
    canvas->tilesPerCol = height;
    canvas->cellSize = cellSize;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Rectangle transform = (Rectangle){j * cellSize, i * cellSize, cellSize, cellSize};
            Rectangle atlasSource = (Rectangle){};
            Tile tile = Tile_init(transform, atlasSource);
            tile.active = false;
            Canvas_setTile(canvas, i, j, tile);
        }
    }
    return canvas;
}

Tile* Canvas_getTile(Canvas* canvas, size_t row, size_t col) {
    if (canvas == NULL) {
        return NULL;
    }
    if (row >= canvas->tilesPerCol || col >= canvas->tilesPerRow) {
        return NULL;
    }
    return &canvas->tiles[row * canvas->tilesPerRow + col];
}

Tile* Canvas_getTileAtCursor(Canvas* canvas, Camera2D* camera) {
    if (canvas == NULL) {
        log_error("canvas is NULL");
        return NULL;
    }
    if (camera == NULL) {
        log_error("camera is NULL");
        return NULL;
    }

    Vector2 mouseScreenPosition = GetMousePosition();
    Vector2 mouseWorldPosition = GetScreenToWorld2D(mouseScreenPosition, *camera);
    int row = (int) mouseWorldPosition.y / canvas->cellSize;
    int col = (int) mouseWorldPosition.x / canvas->cellSize;

    if (row < canvas->tilesPerCol && row >= 0 && col < canvas->tilesPerRow && col >= 0) {
        return Canvas_getTile(canvas, row, col);
    }

    return NULL;
}

int Canvas_draw(Canvas* canvas, TextureAtlas* atlas) {
    if (canvas == NULL) {
        return 1;
    }
    for (size_t row = 0; row < canvas->tilesPerCol; row++) {
        for (size_t col = 0; col < canvas->tilesPerRow; col++) {
            Tile* tileToDraw = Canvas_getTile(canvas, row, col);
            if (tileToDraw == NULL || !tileToDraw->active) {
                continue;
            }
            Tile_draw(tileToDraw, atlas);
        }
    }
    return 0;
}

int Canvas_drawBorder(Canvas* canvas) {
    DrawRectangleLinesEx((Rectangle){
                             0,
                             0,
                             canvas->tilesPerRow * canvas->cellSize,
                             canvas->tilesPerCol * canvas->cellSize
                         }, 2, WHITE);
    return 0;
}

int Canvas_drawTileHighlight(Canvas* canvas, Camera2D* camera) {
    if (canvas == NULL) {
        log_error("canvas is NULL");
        return 1;
    }
    Tile* tile = Canvas_getTileAtCursor(canvas, camera);
    if (tile == NULL) {
        return 1;
    }

    DrawRectangleLinesEx(tile->transform, CANVAS_HIGHLIGHT_THICKNESS, CANVAS_HIGHLIGHT_COLOR);
    return 0;
}

void Canvas_free(Canvas* canvas) {
    free(canvas->tiles);
    free(canvas);
}
