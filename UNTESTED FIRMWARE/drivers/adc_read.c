#include <stdio.h>
#include "adc_read.h"

int adc_read(const char *path)
{
	FILE *f;
	int val = -1;

	f = fopen(path, "r");
	if (!f)
		return -1;
	if (fscanf(f, "%d", &val) != 1)
		val = -1;
	fclose(f);
	return val;
}
