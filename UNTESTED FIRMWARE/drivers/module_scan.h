#ifndef MODULE_SCAN_H
#define MODULE_SCAN_H

#define MOD_COUNT 10

struct module {
	const char *name;
	int slot;
	int on;
};

void scan_init(void);
int scan_modules(struct module *list);
void save_modules(struct module *list, const char *path);

#endif
