#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include "../drivers/fb_screen.h"
#include "../drivers/touch_input.h"
#include "../drivers/gpio_pin.h"
#include "../drivers/mbp_pins.h"
#include "../drivers/module_scan.h"

#define APP_DIR    "/root/mbp/apps"
#define MOD_FILE   "/tmp/mbp_modules"
#define TOUCH_DEV  "/dev/input/event0"
#define MAX_APPS   12
#define MAX_LINES  24

static char apps[MAX_APPS][32];
static int app_count;
static struct module mods[MOD_COUNT];
static int mod_on;
static int sz, bar_h, tile_w, tile_h, gap;

static void find_apps(void)
{
	DIR *d;
	struct dirent *e;
	char *dot;

	app_count = 0;
	d = opendir(APP_DIR);
	if (!d)
		return;
	while ((e = readdir(d)) && app_count < MAX_APPS) {
		dot = strrchr(e->d_name, '.');
		if (!dot || strcmp(dot, ".sh") != 0)
			continue;
		snprintf(apps[app_count], sizeof(apps[0]), "%.*s", (int)(dot - e->d_name), e->d_name);
		app_count++;
	}
	closedir(d);
}

static void draw_bar(void)
{
	char s[20];

	screen_rect(0, 0, screen_w(), bar_h, GREY);
	screen_text(gap, (bar_h - 7 * sz) / 2, "MBP", sz, WHITE);
	snprintf(s, sizeof(s), "%d modules", mod_on);
	screen_text(screen_w() - gap - text_w(s, sz), (bar_h - 7 * sz) / 2, s, sz, WHITE);
}

static void draw_home(void)
{
	int i, x, y;

	screen_clear(BLACK);
	draw_bar();
	for (i = 0; i < app_count; i++) {
		x = gap + (i % 2) * (tile_w + gap);
		y = bar_h + gap + (i / 2) * (tile_h + gap);
		screen_rect(x, y, tile_w, tile_h, BLUE);
		screen_text(x + (tile_w - text_w(apps[i], sz)) / 2, y + (tile_h - 7 * sz) / 2, apps[i], sz, WHITE);
	}
	if (app_count == 0)
		screen_text(gap, bar_h + gap, "no apps", sz, RED);
}

static int tile_at(int tx, int ty)
{
	int i, x, y;

	for (i = 0; i < app_count; i++) {
		x = gap + (i % 2) * (tile_w + gap);
		y = bar_h + gap + (i / 2) * (tile_h + gap);
		if (tx >= x && tx < x + tile_w && ty >= y && ty < y + tile_h)
			return i;
	}
	return -1;
}

static void run_app(int n)
{
	char cmd[96], line[64];
	FILE *p;
	int y, col;

	screen_clear(BLACK);
	draw_bar();
	snprintf(cmd, sizeof(cmd), "sh %s/%s.sh", APP_DIR, apps[n]);
	p = popen(cmd, "r");
	y = bar_h + gap;
	while (p && fgets(line, sizeof(line), p) && y < screen_h() - bar_h * 2) {
		line[strcspn(line, "\n")] = 0;
		col = WHITE;
		if (strstr(line, " yes"))
			col = GREEN;
		if (strstr(line, " no"))
			col = RED;
		screen_text(gap, y, line, sz, col);
		y += 10 * sz;
	}
	if (p)
		pclose(p);

	screen_rect(0, screen_h() - bar_h, screen_w(), bar_h, GREY);
	screen_text((screen_w() - text_w("back", sz)) / 2, screen_h() - bar_h + (bar_h - 7 * sz) / 2, "back", sz, WHITE);
}

static int back_pressed(void)
{
	return gpio_get(BUT_UP, PULL_UP) == 0;
}

int main(void)
{
	int x, y, app = -1, t;
	time_t last = 0;

	if (screen_open() < 0) {
		printf("no screen\n");
		return 1;
	}
	scan_init();
	touch_open(TOUCH_DEV, screen_w(), screen_h());

	sz = screen_w() / 180;
	if (sz < 2)
		sz = 2;
	gap = 4 * sz;
	bar_h = 14 * sz;
	tile_w = (screen_w() - gap * 3) / 2;
	tile_h = tile_w * 2 / 3;

	find_apps();
	mod_on = scan_modules(mods);
	save_modules(mods, MOD_FILE);
	draw_home();

	while (1) {
		if (time(NULL) - last >= 2) {
			last = time(NULL);
			t = mod_on;
			mod_on = scan_modules(mods);
			save_modules(mods, MOD_FILE);
			if (t != mod_on) {
				if (app < 0)
					draw_home();
				else
					run_app(app);
			}
		}

		if (touch_tap(&x, &y)) {
			if (app < 0) {
				app = tile_at(x, y);
				if (app >= 0)
					run_app(app);
			} else if (y > screen_h() - bar_h) {
				app = -1;
				draw_home();
			}
		}

		if (app >= 0 && back_pressed()) {
			app = -1;
			draw_home();
		}

		usleep(20000);
	}
	return 0;
}
