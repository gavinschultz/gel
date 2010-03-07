#include    "SDL.h"
#include    <windows.h>
#include    "GLee.h"
#include    "graphics.h"
#include    "debug.h"

static struct GFX_Res best_res;
static struct GFX_Res current_res;
static int fullscreen = DEFAULT_FULLSCREEN;
static int bitdepth = DEFAULT_COLORDEPTH;
static int vsync = 1;
static SDL_Surface *screen = NULL;
GLfloat gx_axis;
GLfloat gy_axis;
GLfloat gx_scale;
GLfloat gy_scale;

void init_gfx(const GLfloat x_axis, const GLfloat y_axis)
{
    const SDL_VideoInfo *video_info;
    static int best_hres;
    static int best_vres;
    uint32_t video_flags = 0;

    video_info = SDL_GetVideoInfo();
    if (video_info == NULL)
    {
        trace("Could not obtain SDL video info.");
        exit(1);
    }

    if (video_info->hw_available)
    {
        video_flags |= SDL_HWSURFACE;
    }
    else
    {
        video_flags |= SDL_SWSURFACE;
    }

    // Can set the best resolution once, before we have switched to any other video mode
    if (best_res.h == 0 || best_res.v == 0)
    {
        best_res.h = video_info->current_w;
        best_res.v = video_info->current_h;
    }

    if (fullscreen)
    {
        SDL_ShowCursor(SDL_DISABLE);
        video_flags |= SDL_FULLSCREEN;
        current_res.h = best_res.h;
        current_res.v = best_res.v;
    }
    else
    {
        SDL_ShowCursor(SDL_ENABLE);
        current_res.h = DEFAULT_HRES;
        current_res.v = DEFAULT_VRES;
    }

    bitdepth = DEFAULT_COLORDEPTH;
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    screen = SDL_SetVideoMode(current_res.h, current_res.v, bitdepth, video_flags | SDL_OPENGL | SDL_ANYFORMAT | SDL_RESIZABLE);
    if (screen == NULL)
    {
        trace("SDL video mode setting failure: %s", SDL_GetError());
        exit(1);
    }

    init_gl(current_res.h, current_res.v, x_axis, y_axis);
}

static int init_gl(const GLsizei hRes, const GLsizei vRes, const GLfloat x_axis, const GLfloat y_axis)
{
    GLenum response;

    // Setup rendering state
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    resize_window(hRes, vRes, x_axis, y_axis);

    response = glGetError();
    if (response != GL_NO_ERROR)
    {
        trace("OpenGL error detected: %d", glGetError());
        return 0;
    }

    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glColor3f(1.0f, 1.0f, 1.0f);

    return 1;
}

void resize_window(GLsizei w, GLsizei h, const GLfloat x_axis, const GLfloat y_axis)
{
    GLfloat aspect_ratio;
    GLfloat ortho_ratio;
    GLfloat right, left, top, bottom;

    h = (h ? h : 1);
    w = (w ? w : 1);
    gx_axis = x_axis;
    gy_axis = y_axis;

    // Set viewport to dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspect_ratio = (GLfloat)w / (GLfloat)h;
    ortho_ratio = x_axis / y_axis;

    if (aspect_ratio <= ortho_ratio)
    {
        gy_scale = (ortho_ratio / aspect_ratio);
        gx_scale = 1.0f;
    }
    else
    {
        gy_scale = 1.0f;
        gx_scale = (aspect_ratio / ortho_ratio);
    }
    left   = -x_axis * gx_scale;  right = x_axis * gx_scale;
    bottom = -y_axis * gy_scale;  top   = y_axis * gy_scale;

    trace("left: %f right: %f bottom: %f top: %f", left, right, bottom, top);
    gluOrtho2D(left, right, bottom, top);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void toggle_fullscreen()
{
    fullscreen = !fullscreen;
    init_gfx(gx_axis, gy_axis);
}

void toggle_vsync()
{
    vsync = !vsync;
    if (GLEE_WGL_EXT_swap_control)
        wglSwapIntervalEXT(vsync);
}

void int_to_rgb(const uint32_t color, struct RGBColor *rgb_color)
{
    if (rgb_color == NULL)
        return;
    rgb_color->r = ((color & 0xFF0000) >> 16) / 255.0f;
    rgb_color->g = ((color & 0xFF00) >> 8) / 255.0f;
    rgb_color->b = (color & 0xFF) / 255.0f;
}

struct GFX_Res get_current_res(void)
{
    struct GFX_Res res;
    res.h = current_res.h;
    res.v = current_res.v;
    return res;
}

struct GFX_Res get_best_res(void)
{
    struct GFX_Res res;
    res.h = best_res.h;
    res.v = best_res.v;
    return res;
}

int is_fullscreen(void)
{
    return fullscreen;
}

void shutdown_gfx()
{
    SDL_FreeSurface(screen);
    screen = NULL;
}
