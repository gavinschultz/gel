#include    <stdlib.h>
#include    <stdio.h>
#include    "ext.h"
#include    "soil.h"
#include    "debug.h"
#include    "SDL_opengl.h"

static int loaded = 0;
static char *data = NULL;
static int texture_w = 0;
static int texture_h = 0;
static GLuint texture = 0;

int load_texture(void);

void init_sprites()
{
    load_texture();
}

int load_texture()
{
    char texture_file[] = "resources\\sample.bmp";
    int channels = 0;

//    texture = SOIL_load_OGL_texture(texture_file, 
//            SOIL_LOAD_AUTO, 
//            SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);

    data = SOIL_load_image(texture_file, &texture_w, &texture_h, &channels, SOIL_LOAD_AUTO);
    glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, texture_w, texture_h,
			  0, GL_RGB, GL_UNSIGNED_BYTE, data );

    return texture;
}

void draw_sprites()
{
    static float theta = 0.0f;
    if (!loaded)
    {
        load_texture();
        loaded = 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);

    glPushMatrix();
    glRotatef( theta, 0.0f, 0.0f, 1.0f );
    glBegin(GL_QUADS);
    glTexCoord2i( 0, texture_h );				
    glVertex2i( 0 - (texture_w/2), 0 - (texture_h/2) );
    glTexCoord2i( texture_w, texture_h );	
    glVertex2i( (texture_w/2), 0 - (texture_h/2) );
    glTexCoord2i( texture_w, 0 );
    glVertex2i( texture_w/2, texture_h/2 );
    glTexCoord2i( 0, 0 );		
    glVertex2i( 0 - (texture_w/2), texture_h/2 );

    glEnd();
    glDisable(GL_TEXTURE_RECTANGLE_ARB);
    glPopMatrix();

    theta += 2.0f;
}

void move_sprites()
{

}

void cleanup_sprites()
{
    if (texture != 0)
        glDeleteTextures(1, &texture);
}
