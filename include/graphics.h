#ifndef  GRAPHICS_INC
#define  GRAPHICS_INC

#include    "SDL_opengl.h"

#define DEFAULT_HRES        1024        /* default horizontal resolution */
#define DEFAULT_VRES        576         /* default vertical resolution */
#define DEFAULT_COLORDEPTH  32          /* default color depth */
#define DEFAULT_FULLSCREEN  0           /* default to full-screen mode? */

struct GFX_Res
{
    GLsizei h, v;
};

struct Graphics
{
    struct GFX_Res res;         // current resolution
    int bitdepth;           // recommended is 32
    int fullscreen;         // 1 = fullscreen, 0 = windowed
    GLfloat y_axis;        // extent of the Y axis from center to each edge. Total height = 2 * y_axis
    GLfloat x_axis;        // extent of the X axis from center to each edge. Total width = 2 * x_axis
};

struct RGBColor
{
    float r;
    float g;
    float b;
};

extern GLfloat gx_axis;
extern GLfloat gy_axis;
extern GLfloat gx_scale;
extern GLfloat gy_scale;

void init_gfx(const GLfloat x_axis, const GLfloat y_axis);
void shutdown_gfx(void);
static int init_gl(const GLsizei hRes, const GLsizei vRes, const GLfloat x_axis, const GLfloat y_axis);
void toggle_fullscreen(void);
void resize_window(GLsizei w, GLsizei h, const GLfloat x_axis, const GLfloat y_axis);
void int_to_rgb(const uint32_t color, struct RGBColor *rgb_color);
struct GFX_Res get_current_res(void);
struct GFX_Res get_best_res(void);
int is_fullscreen(void);

#endif
