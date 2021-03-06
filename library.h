#ifndef LIBRARY_H
#define LIBRARY_H

typedef unsigned short color_t;

int init_graphics();
int exit_graphics();
void clear_screen();
char getkey();
int sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_text(int x, int y, const char *text, color_t c);
void draw_char(int x, int y, const char text, color_t c);
#endif
