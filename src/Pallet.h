#ifndef PALLET_H
#define PALLET_H

#include <stddef.h>
#include "raylib.h"
#include "Tile.h"

#define PALLET_BORDER_THICKNESS 3
#define PALLET_BORDER_COLOR WHITE
#define PALLET_MARGIN 10
#define PALLET_PADDING 10
#define PALLET_GUI_SCALE 2.5f
#define PALLET_HIGHLIGHT_THICKNESS 2
#define PALLET_HIGHLIGHT_COLOR WHITE

typedef struct Canvas Canvas;

typedef struct Pallet {
    bool isHidden;
    Canvas* canvas;
    Tile* selectedTile;
    float guiScale;
} Pallet;

int _loadTextures(Pallet* pallet, TextureAtlas* atlas);

Pallet* Pallet_init(size_t width, size_t height, size_t cellSize, TextureAtlas* atlas);

void Pallet_free(Pallet* pallet);

int Pallet_draw(Pallet* pallet, TextureAtlas* atlas);

Tile* Pallet_getTileAtCursor(Pallet* pallet);

int Pallet_drawTileHighlight(Pallet* pallet);

int Pallet_selectTile(Pallet* pallet, Tile* tile);

#endif //PALLET_H
