#include "graphics.h"
#include "ext.h"
#include "fixed.h"
#include "timing.h"

static float graph_times[512];
static int current_graph_point = 0;

void draw_timing_graph()
{
    int i;
    static fixed current_time = 0;
    static fixed prev_time = 0;
    current_time = get_time();

    graph_times[current_graph_point] = (float)(current_time - prev_time) / 100.0f;
    if (++current_graph_point >= (sizeof(graph_times)/sizeof(graph_times[0])))
        current_graph_point = 0;

    glPushMatrix();
    glTranslatef(-gx_axis, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<sizeof(graph_times)/sizeof(graph_times[0]); i++)
    {
        if (graph_times[i] > 0.0f)
            glVertex2f((i*2.0f), -graph_times[i] * 10.0f);
    }
    glEnd();
    glPopMatrix();

    prev_time = current_time;
}

