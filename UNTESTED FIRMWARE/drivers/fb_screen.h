#ifndef FB_SCREEN_H
#define FB_SCREEN_H

#define BLACK  0x000000
#define WHITE  0xffffff
#define GREY   0x404040
#define GREEN  0x20c040
#define RED    0xd03030
#define BLUE   0x2060d0

int screen_open(void);
int screen_w(void);
int screen_h(void);
void screen_clear(int col);
void screen_rect(int x, int y, int w, int h, int col);
void screen_text(int x, int y, const char *s, int size, int col);
int text_w(const char *s, int size);

#endif
