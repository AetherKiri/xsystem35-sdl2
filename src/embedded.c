/* In-process VM boundary. All longjmp targets and callers are C frames. */
#include "embedded.h"
#include <setjmp.h>
#include <string.h>
#include "system.h"
#include "event.h"

static const struct xsystem35_host *host;
static jmp_buf exit_target;
static int exit_code;
static SDL_Surface *output;
static SDL_Renderer *renderer;

extern int xsystem35_main(int argc, char **argv);

int xsystem35_host_run(const struct xsystem35_host *hooks, const char *root,
                       const char *saves, const char *font) {
    (void)root; /* The host resolves files without changing the process cwd. */
    host = hooks;
    exit_code = 0;
    if(!setjmp(exit_target)) {
        xsystem35_session_reset();
        char *args[] = { "xsystem35",      "-savedir",       (char *)saves,
                         "-ttfont_gothic", (char *)font,     "-ttfont_mincho",
                         (char *)font,     "-noimagecursor", NULL };
        exit_code = xsystem35_main(8, args);
    }
    xsystem35_session_cleanup();
    xsystem35_host_free_renderer();
    host = NULL;
    return exit_code;
}

void xsystem35_host_exit(int code) {
    exit_code = code;
    longjmp(exit_target, 1);
}

void xsystem35_host_checkpoint(void) {
    if(host && host->checkpoint && host->checkpoint(host->user))
        xsystem35_host_exit(0);
}

int xsystem35_host_poll_event(SDL_Event *event) {
    xsystem35_host_checkpoint();
    return host && host->poll_event ? host->poll_event(host->user, event) : 0;
}

SDL_Renderer *xsystem35_host_renderer(int width, int height) {
    if(output && output->w == width && output->h == height)
        return renderer;
    xsystem35_host_free_renderer();
    output = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                            SDL_PIXELFORMAT_RGBA32);
    if(!output || !(renderer = SDL_CreateSoftwareRenderer(output)))
        sys_error("Cannot create embedded renderer: %s", SDL_GetError());
    return renderer;
}

void xsystem35_host_free_renderer(void) {
    if(renderer)
        SDL_DestroyRenderer(renderer);
    renderer = NULL;
    if(output)
        SDL_FreeSurface(output);
    output = NULL;
}

void xsystem35_host_present(void) {
    if(host && host->present && output)
        host->present(host->user, output);
}

void xsystem35_host_text_input(int active) {
    if(host && host->text_input)
        host->text_input(host->user, active);
}

void xsystem35_host_log(int level, const char *message) {
    if(host && host->log)
        host->log(host->user, level, message);
}

int xsystem35_host_gbk(void) { return host && host->gbk_text; }

void xsystem35_host_clear_input(void) { event_reset_input_state(); }
