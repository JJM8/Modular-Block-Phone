#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include "touch_input.h"

static int fd = -1;
static int max_x = 1, max_y = 1;
static int sw, sh;
static int cur_x, cur_y, down;

int touch_open(const char *path, int scr_w, int scr_h)
{
	struct input_absinfo abs;

	fd = open(path, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
		return -1;

	if (ioctl(fd, EVIOCGABS(ABS_X), &abs) == 0 && abs.maximum > 0)
		max_x = abs.maximum;
	if (ioctl(fd, EVIOCGABS(ABS_Y), &abs) == 0 && abs.maximum > 0)
		max_y = abs.maximum;
	sw = scr_w;
	sh = scr_h;
	return 0;
}

int touch_tap(int *x, int *y)
{
	struct input_event ev;

	while (read(fd, &ev, sizeof(ev)) == sizeof(ev)) {
		if (ev.type == EV_ABS && ev.code == ABS_X)
			cur_x = ev.value * sw / max_x;
		if (ev.type == EV_ABS && ev.code == ABS_Y)
			cur_y = ev.value * sh / max_y;
		if (ev.type == EV_KEY && ev.code == BTN_TOUCH) {
			if (ev.value) {
				down = 1;
			} else if (down) {
				down = 0;
				*x = cur_x;
				*y = cur_y;
				return 1;
			}
		}
	}
	return 0;
}
