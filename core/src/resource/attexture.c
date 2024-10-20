#include "../../headers/resource/attexture.h"

void _atDestroyTextureData(ATtextureData* d) {
    d->count = 0;
    atDestroyArray(d->src);
    atDestroyArray(d->title);
    atDestroyArray(d->n_channels);
    atDestroyArray(d->dimensions);
    free(d);
}

ATerrorType _atInitTextureData(ATtextureData* d, int max) {
    d->count = 0;
    d->src = atMakeArray(max, 250);
    d->title = atMakeArray(max, 250);
    d->n_channels = atMakeArray(max, 250);
    d->dimensions = atMakeArray(max, 250);
    return ERR_NONE;
}
