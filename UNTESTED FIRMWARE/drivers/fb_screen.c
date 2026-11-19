#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include "fb_screen.h"
#include "font_5x7.h"

static unsigned int *fb;
static int width, height, stride;

int screen_open(void)
{
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;
	int fd;

	fd = open("/dev/fb0", O_RDWR);
	if (fd < 0)
		return -1;
	if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0 || ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0)
		return -1;
	if (var.bits_per_pixel != 32)
		return -1;

	width = var.xres;
	height = var.yres;
	stride = fix.line_length / 4;
	fb = mmap(NULL, fix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb == MAP_FAILED)
		return -1;
	return 0;
}

int screen_w(void)
{
	return width;
}

int screen_h(void)
{
	return height;
}

void screen_rect(int x, int y, int w, int h, int col)
{
	int i, j;

	if (x < 0) { w += x; x = 0; }
	if (y < 0) { h += y; y = 0; }
	if (x + w > width) w = width - x;
	if (y + h > height) h = height - y;

	for (j = y; j < y + h; j++)
		for (i = x; i < x + w; i++)
			fb[j * stride + i] = col;
}

void screen_clear(int col)
{
	screen_rect(0, 0, width, height, col);
}

static void draw_char(int x, int y, char c, int size, int col)
{
	const unsigned char *g = font_get(toupper((unsigned char)c));
	int i, j;

	for (i = 0; i < 5; i++)
		for (j = 0; j < 7; j++)
			if (g[i] & (1 << j))
				screen_rect(x + i * size, y + j * size, size, size, col);
}

void screen_text(int x, int y, const char *s, int size, int col)
{
	while (*s) {
		draw_char(x, y, *s++, size, col);
		x += 6 * size;
	}
}

int text_w(const char *s, int size)
{
	return strlen(s) * 6 * size - size;
}
