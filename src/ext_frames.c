#include    "ext.h"
#include    "graphics.h"

void draw_frames()
{
    int i;
    GLfloat linesizes[2];
    GLfloat linestep;

    glGetFloatv(GL_LINE_WIDTH_RANGE, linesizes);
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &linestep);

    glPushMatrix();

    // draw axes
    glLineWidth(linesizes[0]);
    glLineStipple(1, 0x1010);
    glBegin(GL_LINES);
    {
        glVertex2f(0.0, -gy_axis);
        glVertex2f(0.0, gy_axis);
        glVertex2f(-gx_axis, 0.0);
        glVertex2f(gx_axis, 0.0);
    }
    glEnd();

    // draw outer frame
    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(-gx_axis + (gx_axis / 40.0f), -gy_axis + (gy_axis / 40.0f));
        glVertex2f(-gx_axis + (gx_axis / 40.0f), gy_axis - (gy_axis / 40.0f));
        glVertex2f(gx_axis - (gx_axis / 40.0f), gy_axis - (gy_axis / 40.0f));
        glVertex2f(gx_axis - (gx_axis / 40.0f), -gy_axis + (gy_axis / 40.0f));
    }
    glEnd();

    glLineStipple(1, 0x3000);
    glBegin(GL_LINES);
    for (i=1; i<3; i++)
    {
        glVertex2f(-gx_axis + ((gx_axis*2.0f*i) / 3), -gy_axis);
        glVertex2f(-gx_axis + ((gx_axis*2.0f*i) / 3), gy_axis);
        glVertex2f(-gx_axis, gy_axis - ((gy_axis*2.0f*i) / 3));
        glVertex2f(gx_axis, gy_axis - ((gy_axis*2.0f*i) / 3));
    }
    glEnd();
    glLineStipple(1, 0xFFFF);
    glPopMatrix();
}
