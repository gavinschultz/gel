#include    <stdlib.h>
#include    <stdio.h>
#include    "gel.h"
#include    "ext.h"
//#include    "soil.h"
#include    "debug.h"
#include    "graphics.h"
#include    "SDL.h"

struct State
{
    float x;    // position
    float v;    // velocity
};

struct Derivative
{
    float dx;   // derivative of position: velocity
    float dv;   // derivative of velocity: acceleration
};

static int loaded = 0;
static GLuint texture = 0;
static float theta = 0.0f;
static int direction = -1;
static struct State current; 
static struct State previous;
static struct State render_state;

const float rect_h = 40.0f;
const float rect_w = 40.0f;

void interpolate(fixed alpha)
{
    static fixed prev_time = 0;
    static float prev_render_x;
    static fixed warning_time = 0;
    fixed current_time = get_time();
    float alphaf = 0.0f;

    if (fabs(current.x - previous.x) > 50.0f)
    {
        trace("Difference too great (%f, %f), not interpolating", current.x, previous.x);
        prev_time = current_time;
        prev_render_x = render_state.x;
        return;
    }

    if (prev_time == 0)
        prev_time = current_time;

    alphaf = fptof(alpha);
	render_state.x = current.x*alphaf + previous.x*(1.0f-alphaf);
	render_state.v = current.v*alphaf + previous.v*(1.0f-alphaf);

    // good
    trace("[%ld] Alpha: %3.2f actual: %3.2f render: %3.2f a/r diff: %3.2f", current_time - prev_time, alphaf, current.x - previous.x, render_state.x - prev_render_x, current.x - render_state.x);

    prev_time = current_time;
    prev_render_x = render_state.x;
}

void init_sprites()
{
    current.x = gx_axis;
    current.v = 0.0f;
}

void draw_sprites()
{
    glPushMatrix();
    glTranslatef( render_state.x, 0.0f, 0.0f );
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glBegin(GL_TRIANGLES);
    glVertex2f( -rect_w/2.0f, -rect_h/2.0f );
    glVertex2f( -rect_w/2.0f, rect_h/2.0f );
    glVertex2f( rect_w/2.0f, rect_h/2.0f );
    glVertex2f( rect_w/2.0f, -rect_h/2.0f );
    glEnd();
    glPopMatrix();
}

void move_sprites(fixed t, fixed dt)
{
    previous = current;

    current.x += direction * (float)dt / (float)200.0f;

//    if ((current.x <= -gx_axis && direction == -1) || (current.x >= gx_axis && direction == 1))
    if ((direction * current.x) >= gx_axis)
        direction = -direction;

    render_state.x = current.x;
}

void cleanup_sprites()
{
}
