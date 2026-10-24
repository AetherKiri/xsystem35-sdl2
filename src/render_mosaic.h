#ifndef XSYSTEM35_RENDER_MOSAIC_H
#define XSYSTEM35_RENDER_MOSAIC_H
#include "sdl_compat.h"

/* Downsample then magnify within bounded rectangles. Software SDL renderers
 * cannot safely blit a whole texture to the enormous, negatively positioned
 * rectangle used by the original GPU implementation. */
bool render_mosaic(SDL_Renderer *renderer, SDL_Texture *source,
                   const SDL_Rect *source_rect, SDL_Texture *temporary,
                   SDL_Texture *destination, int width, int height,
                   float scale);
#endif
