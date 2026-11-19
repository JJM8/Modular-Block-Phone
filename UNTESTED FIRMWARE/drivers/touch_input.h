#ifndef TOUCH_INPUT_H
#define TOUCH_INPUT_H

int touch_open(const char *path, int scr_w, int scr_h);
int touch_tap(int *x, int *y);

#endif
