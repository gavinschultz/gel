#include    "ext.h"
#include    "SDL_opengl.h"
#include    "graphics.h"

static float x;
static float y;
static const float w = 25.0f;
static const float h = 25.0f;

void draw_primitives()
{
    glPushMatrix();
    glLineWidth(2.0f);
    glBegin(GL_QUADS);
    glVertex2f(x-(w/2), y-(h/2));
    glVertex2f(x-(w/2), y+(h/2));
    glVertex2f(x+(w/2), y+(h/2));
    glVertex2f(x+(w/2), y-(h/2));
    glEnd();
    glPopMatrix();
}

void move_primitives()
{
    x += 3.2f;
    y += 1.8f;

    if (x > gx_axis)
        x = x - (2*gx_axis);
    if (y > gy_axis)
        y = y - (2*gy_axis);
}
