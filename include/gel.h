#ifndef  GEL_INC
#define  GEL_INC

#include    <stdlib.h>
#include    <stdio.h>
#include    <math.h>
#include    <time.h>
#include    "SDL.h"
#include    "debug.h"
#include    "graphics.h"
#include    "timing.h"
#include    "util.h"

#define FPS                 60.0f       /* frames per second */

struct App
{
    int quit;
    int paused;
};

extern struct App app;

void init(void);
void shutdown(void);
void handle_event(SDL_Event *event);
void init_objects(void);
void move_objects(void);
void draw_scene(void);
void cleanup(void);
#endif
