#include "../../headers/resource/attexture.h"

void _atDestroyTextureData(ATtextureData* d) {
    d->count = 0;
    free(d->src);
    free(d->title);
    free(d->n_channels);
    free(d->dimensions);
    free(d);
}

ATerrorType _atInitTextureData(ATtextureData* d, int max) {
    d->count = 0;

    if (atInitCharPointerArray(&d->src, max, 256, "texture data [src]")) {
        atLogError("failed to allocate texture data [src] array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->n_channels, max, "texture data [n channels]")) {
        atLogError("failed to allocate texture data [n channels] array");
        return ERR_MALLOC;
    }

    if (atInitCharPointerArray(&d->title, max, 256, "texture data [title]")) {
        atLogError("failed to allocate texture data [title] array");
        return ERR_MALLOC;
    }

    if (atInitIntPointerArray(&d->dimensions, max, 2, "texture data [dimensions]")) {
        atLogError("failed to allocate texture data [dimensions] array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}
