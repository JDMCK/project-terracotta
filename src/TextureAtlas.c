#include <stddef.h>
#include <stdlib.h>
#include "raylib.h"
#include "TextureAtlas.h"

#include "Editor.h"
#include "utils.h"

TextureAtlas* TextureAtlas_init(const char* filePath, size_t tileWidth, size_t tileHeight, size_t tileCount) {
    if (!FileExists(filePath)) {
        log_error("File does not exist at path: %s\n", filePath);
        return NULL;
    }

    TextureAtlas* textureAtlas = calloc(1, sizeof(TextureAtlas));
    if (textureAtlas == NULL) {
        log_error("Failed to allocate texture atlas\n");
        return NULL;
    }

    Texture2D texture = LoadTexture(filePath);
    size_t width = texture.width / tileWidth;
    size_t height = texture.height / tileHeight;

    textureAtlas->texture = texture;
    textureAtlas->width = width;
    textureAtlas->height = height;
    textureAtlas->tileWidth = tileWidth;
    textureAtlas->tileHeight = tileHeight;
    textureAtlas->tileCount = tileCount;

    return textureAtlas;
}

// Pallet* TextureAtlas_getPallet(TextureAtlas* textureAtlas) {
//     Pallet* pallet = Pallet_init(8, 2, CANVAS_CELL_SIZE);
//     for (size_t i = 0; i < textureAtlas->tileCount; i++) {
//         Tile tile = (Tile){true,}
//         size_t row = i / textureAtlas->width;
//         size_t col = i % textureAtlas->width;
//         pallet[row * textureAtlas->width + col] =
//     }
// }
