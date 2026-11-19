#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include "gpio_pin.h"

#define MAX_OUT 8

static int chip_fd = -1;
static int out_pin[MAX_OUT];
static int out_fd[MAX_OUT];
static int out_count;

int gpio_open(void)
{
	chip_fd = open("/dev/gpiochip0", O_RDWR);
	return chip_fd < 0 ? -1 : 0;
}

int gpio_get(int pin, int pull)
{
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	int val;

	memset(&req, 0, sizeof(req));
	req.lineoffsets[0] = pin;
	req.lines = 1;
	req.flags = GPIOHANDLE_REQUEST_INPUT;
	if (pull == PULL_UP)
		req.flags |= GPIOHANDLE_REQUEST_BIAS_PULL_UP;
	if (pull == PULL_DOWN)
		req.flags |= GPIOHANDLE_REQUEST_BIAS_PULL_DOWN;
	strcpy(req.consumer_label, "mbp");

	if (ioctl(chip_fd, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0)
		return -1;

	usleep(1000);
	val = -1;
	if (ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) == 0)
		val = data.values[0];
	close(req.fd);
	return val;
}

int gpio_set(int pin, int val)
{
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	int i;

	for (i = 0; i < out_count; i++) {
		if (out_pin[i] == pin) {
			data.values[0] = val;
			return ioctl(out_fd[i], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		}
	}

	if (out_count == MAX_OUT)
		return -1;

	memset(&req, 0, sizeof(req));
	req.lineoffsets[0] = pin;
	req.lines = 1;
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	req.default_values[0] = val;
	strcpy(req.consumer_label, "mbp");

	if (ioctl(chip_fd, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0)
		return -1;

	out_pin[out_count] = pin;
	out_fd[out_count] = req.fd;
	out_count++;
	return 0;
}
