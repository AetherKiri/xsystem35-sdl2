#include "render_mosaic.h"
#include <math.h>

static bool set_target(SDL_Renderer *renderer, SDL_Texture *texture) {
#if XSYSTEM35_SDL_VERSION == 2
    return SDL_SetRenderTarget(renderer, texture) == 0;
#else
    return SDL_SetRenderTarget(renderer, texture);
#endif
}

bool render_mosaic(SDL_Renderer *renderer, SDL_Texture *source,
                   const SDL_Rect *source_rect, SDL_Texture *temporary,
                   SDL_Texture *destination, int width, int height,
                   float scale) {
    if(!renderer || !source || !temporary || !destination || width <= 0 ||
       height <= 0)
        return false;
    if(!isfinite(scale) || scale < 1.f)
        scale = 1.f;
    SDL_Rect sample = { 0, 0, (int)ceilf(width / scale),
                        (int)ceilf(height / scale) };
    if(sample.w < 1)
        sample.w = 1;
    if(sample.h < 1)
        sample.h = 1;
    SDL_Rect full = { 0, 0, width, height };
    if(!set_target(renderer, temporary))
        return false;
    sdl_RenderTexture(renderer, source, source_rect, &sample);
    if(!set_target(renderer, destination)) {
        SDL_SetRenderTarget(renderer, NULL);
        return false;
    }
    SDL_SetTextureScaleMode(temporary, SDL_SCALEMODE_NEAREST);
    sdl_RenderTexture(renderer, temporary, &sample, &full);
    return set_target(renderer, NULL);
}
