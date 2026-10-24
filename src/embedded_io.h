/* Force-included only by the embedded target, after the platform declarations.
 * Resolve game-relative paths locally; never change Aether's process cwd. */
#ifndef XSYSTEM35_EMBEDDED_IO_H
#define XSYSTEM35_EMBEDDED_IO_H
#include "embedded_symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "embedded.h"
#define fopen(path, mode)                                                      \
    fopen(xsystem35_host_path(path,                                            \
                              (mode)[0] != 'r' || strchr(mode, '+') != NULL),  \
          mode)
#define opendir(path) opendir(xsystem35_host_path(path, 0))
#define access(path, mode) access(xsystem35_host_path(path, 0), mode)
#define stat(path, buffer) stat(xsystem35_host_path(path, 0), buffer)
#define open(path, flags, ...)                                                 \
    open(xsystem35_host_path(path,                                             \
                             ((flags) & (O_WRONLY | O_RDWR | O_CREAT)) != 0),  \
         flags, ##__VA_ARGS__)
#define rename(from, to)                                                       \
    rename(xsystem35_host_path(from, 1), xsystem35_host_path(to, 1))
#define unlink(path) unlink(xsystem35_host_path(path, 1))
#define mkdir(path, mode) mkdir(xsystem35_host_path(path, 1), mode)
#define Mix_LoadMUS(path) Mix_LoadMUS(xsystem35_host_path(path, 0))
#define SDL_RWFromFile(path, mode)                                             \
    SDL_RWFromFile(xsystem35_host_path(path, (mode)[0] != 'r'), mode)
#define FT_New_Face(library, path, index, face)                                \
    FT_New_Face(library, xsystem35_host_path(path, 0), index, face)
#endif
