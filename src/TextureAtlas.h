#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include <stddef.h>

#include "Tile.h"
#include "Pallet.h"

typedef struct TextureAtlas {
    const char* filePath;
    Texture2D texture;
    size_t width;
    size_t height;
    size_t tileWidth;
    size_t tileHeight;
    size_t tileCount;
} TextureAtlas;

TextureAtlas* TextureAtlas_init(const char* filePath, size_t tileWidth, size_t tileHeight, size_t tileCount);

Pallet* TextureAtlas_getPallet(TextureAtlas* textureAtlas);

#endif //TEXTUREATLAS_H
