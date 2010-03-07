#include    "gel.h"
#include    "ext.h"
#include    "fixed.h"
#include    "graphics.h"

#define Y_AXIS              288.0f      /* extent of y-axis */
#define X_AXIS              512.0f      /* extent of x-axis */

struct App app;
void (*init_func[])() = { init_sprites };
void (*draw_func[])() = { draw_frames, draw_sprites, draw_timing_graph, draw_text };
void (*move_func[])(fixed, fixed) = { move_sprites };
void (*cleanup_func[])() = { cleanup_sprites };

int main(int argc, char *argv[])
{
    const fixed dt = (1 << FIXPOINT_SHIFT) / 100;   // 60 FPS
    fixed t = 0;
    fixed accumulator = 0;
    fixed delta_time = 0;
    SDL_Event event;

    init();

    while (!app.quit)
    {
        start_frame();

        delta_time = get_last_frame_time();

        if (SDL_PollEvent(&event))
        {
            handle_event(&event);
        }

        if (!app.paused)
        {
            accumulator += delta_time;
//            trace("accumulator %ld, dt: %ld, delta_time %ld", accumulator, dt, delta_time);

            while (accumulator >= dt)
            {
                move_objects(t, dt);
                t += dt;
                accumulator -= dt;
            }

            interpolate(fpdiv(accumulator, dt));

            draw_scene();
        }

        end_frame();
    }

    return 0;
}

void init()
{
//    HANDLE hCurrentProcess = GetCurrentProcess();
//    SetPriorityClass(hCurrentProcess, REALTIME_PRIORITY_CLASS);

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        trace("SDL initialization failed: %s.", SDL_GetError());
        exit(1);
    }

    atexit(shutdown_app);
    srand((unsigned int)time(NULL));

    // Graphics init
    init_gfx(X_AXIS, Y_AXIS);

    init_objects();
}

void shutdown_app()
{
    cleanup();
    shutdown_gfx();
}

void handle_event(SDL_Event *event)
{
    SDLKey key = SDLK_CLEAR;

    if (event == NULL)
        return;

    // These events may be used at any time, even when the game is paused
    switch(event->type)
    {
        case SDL_QUIT:
            app.quit = 1;
            break;
        case SDL_KEYDOWN:
            key = event->key.keysym.sym;
            switch(key)
            {
                case SDLK_q:
                case SDLK_ESCAPE:
                    app.quit = 1;
                    break;
                case SDLK_p:
                    app.paused = (app.paused ? 0 : 1);
                    break;
                case SDLK_RETURN:
                    if (event->key.keysym.mod & KMOD_ALT)
                    {
                        toggle_fullscreen();
                        init_objects();
                    }
                    break;
                case SDLK_v:
                    toggle_vsync();
                    break;
            }
            break;
        case SDL_VIDEORESIZE:
            resize_window(event->resize.w, event->resize.h, X_AXIS, Y_AXIS);
            break;
    }
}

void init_objects()
{
    int i;
    for (i=0; i<(sizeof(init_func) / sizeof(*init_func)); i++)
    {
        init_func[i]();
    }
}

void move_objects(fixed t, fixed dt)
{
    int i;

    for (i=0; i<(sizeof(move_func) / sizeof(*move_func)); i++)
    {
        move_func[i](t, dt);
    }
}

void draw_scene()
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);

    for(i=0; i<(sizeof(draw_func) / sizeof(*draw_func)); i++)
    {
        draw_func[i]();
    }

    SDL_GL_SwapBuffers();
}


void cleanup()
{
    int i;

    for(i=0; i<(sizeof(cleanup_func) / sizeof(*cleanup_func)); i++)
    {
        cleanup_func[i]();
    }
}
