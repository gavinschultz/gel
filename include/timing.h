#include    "SDL.h"

#define TIMETRACE       0       /* Enable / disable time tracing */
#define DEFAULT_FPS     60      /* default frames per second */
#define MAX_FPS         200     /* maximum frames per second */

void set_fps(int);
void start_frame(void);
void end_frame(void);
void timetrace(char *,...);
float get_frame_rate(void);
uint32_t get_frame_ticks(void);     // Gets the raw number of ticks at the time this frame started
uint32_t get_elapsed_ticks(void);   // Gets the number of ticks elapsed since last frame
