/* Native embedding interface used by Aether. Standalone builds are unchanged.
 */
#ifndef XSYSTEM35_EMBEDDED_H
#define XSYSTEM35_EMBEDDED_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

struct xsystem35_host {
    void *user;
    int gbk_text;
    void (*present)(void *user, const SDL_Surface *surface);
    int (*poll_event)(void *user, SDL_Event *event);
    int (*checkpoint)(void *user);
    void (*text_input)(void *user, int active);
    void (*log)(void *user, int level, const char *message);
};

int xsystem35_host_run(const struct xsystem35_host *host, const char *root,
                       const char *saves, const char *font);
void xsystem35_host_exit(int code);
int xsystem35_host_gbk(void);
void xsystem35_host_checkpoint(void);
int xsystem35_host_poll_event(SDL_Event *event);
void xsystem35_host_present(void);
void xsystem35_host_text_input(int active);
void xsystem35_host_clear_input(void);
void xsystem35_host_log(int level, const char *message);
SDL_Renderer *xsystem35_host_renderer(int width, int height);
void xsystem35_host_free_renderer(void);
const char *xsystem35_host_path(const char *path, int write);
void xsystem35_session_reset(void);
void xsystem35_session_cleanup(void);

#ifdef __cplusplus
}
#endif
#endif
