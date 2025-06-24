#include "utils.h"

#include <stdio.h>
#include <stdarg.h>

void log_error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void printTile(Tile* tile) {
    printf("Tile:\nActive: %d\nTransform: %f, %f, %f, %f\nAtlasSource: %f, %f, %f, %f\n",
           tile->active,
           tile->transform.x,
           tile->transform.y,
           tile->transform.width,
           tile->transform.height,
           tile->atlasSource.x,
           tile->atlasSource.y,
           tile->atlasSource.width,
           tile->atlasSource.height);
}
