#include    <FTGL/ftgl.h>
#include    "graphics.h"
#include    "debug.h"
#include    "timing.h"
#include    "fixed.h"
#include    "ext.h"

static FTGLfont *font = NULL;
static const char fontname[] = "consola.ttf";
static float sum_frame_rate = 0.0f;
static float avg_frame_rate = 0.0f;
static int cnt_frame = 0;
static fixed elapsed_time = 0;

void draw_text()
{
    char message[100];

    cnt_frame++;
    sum_frame_rate += get_frame_rate();
    elapsed_time += get_last_frame_time();
    if (elapsed_time >= ftofp(0.25f))
    {
//        trace("sum_frame_rate: %5.1f cnt_frame: %d", sum_frame_rate, cnt_frame);
        avg_frame_rate = sum_frame_rate / (float)cnt_frame;
        sum_frame_rate = 0.0f;
        cnt_frame = 0;
        elapsed_time = 0;
    }

    sprintf(message, "%4.1f FPS", avg_frame_rate);

    /* Initialise FTGL stuff */
    if (font == NULL)
    {
        font = ftglCreateBitmapFont(fontname);
        if(!font)
        {
            trace("Could not load font %s", fontname);
            exit(1);
        }

        ftglSetFontFaceSize(font, 10, 72);
        ftglSetFontCharMap(font, ft_encoding_unicode);
    }

    glPushMatrix();
    glRasterPos2f(-gx_axis, gy_axis - 10.0f);
    ftglRenderFont(font, message, FTGL_RENDER_ALL);
    glPopMatrix();
}

void move_text()
{

}
