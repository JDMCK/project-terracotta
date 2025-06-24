#include "Pallet.h"

#include <stdio.h>
#include <stdlib.h>
#include "Canvas.h"
#include "utils.h"

int _loadTextures(Pallet* pallet, TextureAtlas* atlas) {
    if (pallet->canvas == NULL) {
        log_error("Pallet canvas is NULL");
        return 1;
    }

    size_t cellSize = pallet->canvas->cellSize;
    size_t offset = PALLET_MARGIN + PALLET_PADDING;
    for (size_t i = 0; i < atlas->tileCount; i++) {
        float x = (float) (i % pallet->canvas->tilesPerRow * cellSize);
        float y = (float) (i / pallet->canvas->tilesPerRow * cellSize);
        float scale = pallet->guiScale;
        Rectangle transform = (Rectangle){
            x * scale + offset,
            y * scale + offset,
            cellSize * scale,
            cellSize * scale
        };
        Rectangle atlasSrc = (Rectangle){x, y, cellSize, cellSize};
        Tile tile = Tile_init(transform, atlasSrc);
        if (Canvas_setTileIndex(pallet->canvas, i, tile)) {
            return 1;
        }
    }
    return 0;
}

Pallet* Pallet_init(size_t width, size_t height, size_t cellSize, TextureAtlas* atlas) {
    Pallet* pallet = calloc(1, sizeof(Pallet));
    Canvas* canvas = Canvas_init(width, height, cellSize);

    pallet->canvas = canvas;
    pallet->isHidden = false;
    pallet->selectedTile = NULL;
    pallet->guiScale = PALLET_GUI_SCALE;

    _loadTextures(pallet, atlas);
    return pallet;
}

void Pallet_free(Pallet* pallet) {
    Canvas_free(pallet->canvas);
    free(pallet);
}

int Pallet_draw(Pallet* pallet, TextureAtlas* atlas) {
    size_t cellSize = pallet->canvas->cellSize;
    Rectangle palletBorder = (Rectangle){};
    palletBorder.x = PALLET_MARGIN;
    palletBorder.y = PALLET_MARGIN;
    palletBorder.width = cellSize * pallet->canvas->tilesPerRow * pallet->guiScale + PALLET_MARGIN * 2;
    palletBorder.height = cellSize * pallet->canvas->tilesPerCol * pallet->guiScale + PALLET_MARGIN * 2;
    // Draw Pallet border
    DrawRectangleLinesEx(palletBorder, PALLET_BORDER_THICKNESS, PALLET_BORDER_COLOR);
    // Draw tiles
    Canvas_draw(pallet->canvas, atlas);
    // Draw selectedTile
    if (pallet->selectedTile != NULL) {
        DrawRectangleLinesEx(pallet->selectedTile->transform, PALLET_HIGHLIGHT_THICKNESS, PALLET_HIGHLIGHT_COLOR);
    }
    return 0;
}

Tile* Pallet_getTileAtCursor(Pallet* pallet) {
    if (pallet == NULL) {
        log_error("pallet is NULL");
        return NULL;
    }

    Vector2 mousePosition = GetMousePosition();
    float row = (mousePosition.y - PALLET_MARGIN - PALLET_PADDING) / pallet->guiScale / pallet->canvas->cellSize;
    float col = (mousePosition.x - PALLET_MARGIN - PALLET_PADDING) / pallet->guiScale / pallet->canvas->cellSize;
    if (row < pallet->canvas->tilesPerCol && row >= 0 && col < pallet->canvas->tilesPerRow && col >= 0) {
        return Canvas_getTile(pallet->canvas, row, col);
    }

    return NULL;
}

int Pallet_drawTileHighlight(Pallet* pallet) {
    if (pallet == NULL) {
        log_error("pallet is NULL");
        return 1;
    }
    Tile* highlightedTile = Pallet_getTileAtCursor(pallet);
    if (highlightedTile == NULL) {
        return 1;
    }
    DrawRectangleLinesEx(highlightedTile->transform, PALLET_HIGHLIGHT_THICKNESS, PALLET_HIGHLIGHT_COLOR);
    return 0;
}

int Pallet_selectTile(Pallet* pallet, Tile* tile) {
    if (pallet == NULL || tile == NULL) {
        return 1;
    }
    pallet->selectedTile = tile;
    return 0;
}
