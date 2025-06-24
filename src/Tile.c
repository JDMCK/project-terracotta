#include <stdio.h>

#include "Tile.h"
#include "raylib.h"
#include "TextureAtlas.h"
#include "utils.h"

Tile Tile_init(Rectangle transform, Rectangle atlasSource) {
    return (Tile){true, transform, atlasSource};
}

void Tile_draw(Tile* tile, TextureAtlas* atlas) {
    // printf("Tile transform: %f, %f\n", tile->transform.x, tile->transform.y);
    DrawTexturePro(atlas->texture, tile->atlasSource, tile->transform, (Vector2){0, 0}, 0.f, WHITE);
}

int Tile_set(Tile* self, Tile* selectedTile) {
    if (self == NULL || selectedTile == NULL) {
        log_error("a tile is null");
        return 1;
    }
    self->active = true;
    self->atlasSource = selectedTile->atlasSource;
}

int Tile_unset(Tile* self) {
    self->active = false;
    self->atlasSource = (Rectangle){0, 0, 0, 0};
}
