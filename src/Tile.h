#ifndef TILE_H
#define TILE_H

#include "raylib.h"

typedef struct TextureAtlas TextureAtlas;

typedef struct Tile {
    bool active;
    Rectangle transform;
    Rectangle atlasSource;
} Tile;

Tile Tile_init(Rectangle transform, Rectangle atlasSource);

void Tile_draw(Tile* tile, TextureAtlas* atlas);

int Tile_set(Tile* self, Tile* selectedTile);

int Tile_unset(Tile* self);

#endif
