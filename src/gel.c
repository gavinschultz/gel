#include    "gel.h"
#include    "ext.h"

#define Y_AXIS              288.0f      /* extent of y-axis */
#define X_AXIS              512.0f      /* extent of x-axis */

struct App app;
void (*init_func[])() = { init_sprites };
void (*draw_func[])() = { draw_sprites, draw_text, draw_frames, draw_primitives };
void (*move_func[])() = { move_sprites, move_primitives };
void (*cleanup_func[])() = { cleanup_sprites };

//TODO: Have partially implemented time / physics separation as per http://gafferongames.com/game-physics/fix-your-timestep/
//However still need to implement the "integrate" part, which may make the end result a bit smoother
int main(int argc, char *argv[])
{
    const uint32_t dt = 10;
    uint32_t accumulator = 0;
    int32_t delta_time = 0;

    SDL_Event event;

    init();

    while (!app.quit)
    {
        start_frame();

        if (SDL_PollEvent(&event))
        {
            handle_event(&event);
        }

        delta_time = get_elapsed_ticks();

        if (!app.paused)
        {
            if (delta_time > 250)
                delta_time = 250;

            accumulator += delta_time;
//            trace("[%d ticks] accumulator: %d dt: %d", SDL_GetTicks(), accumulator, dt);

            while (accumulator >= dt)
            {
                // integrate
                move_objects();
//                trace("[%d ticks] accumulator >= dt (%d >= %d)", SDL_GetTicks(), accumulator, dt);
//                t += dt;
                accumulator -= dt;
            }

            draw_scene();
        }

        end_frame();
    }

    return 0;
}

void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        trace("SDL initialization failed: %s.", SDL_GetError());
        exit(1);
    }

    atexit(shutdown);
    srand((unsigned int)time(NULL));

    // Timing init
    set_fps((int)FPS);

    // Graphics init
    init_gfx(X_AXIS, Y_AXIS);

    init_objects();
}

void shutdown()
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
            }
            break;
        case SDL_VIDEORESIZE:
            resize_window(event->resize.w, event->resize.h, X_AXIS, Y_AXIS);
//            init_objects();
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

void move_objects()
{
    int i;

    for (i=0; i<(sizeof(move_func) / sizeof(*move_func)); i++)
    {
        move_func[i]();
    }
}

void draw_scene()
{
    int i;

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
