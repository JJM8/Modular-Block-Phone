#include <stdio.h>
#include <unistd.h>
#include "mbp_pins.h"
#include "gpio_pin.h"
#include "i2c_bus.h"
#include "adc_read.h"
#include "uart_port.h"
#include "module_scan.h"

static int cam_fd = -1;
static int imu_fd = -1;
static int wifi_fd = -1;

void scan_init(void)
{
	gpio_open();
	cam_fd = i2c_open(CAM_BUS);
	imu_fd = i2c_open(IMU_BUS);
	wifi_fd = uart_open(WIFI_UART);
	gpio_set(CAM_PWDN, 0);
	gpio_set(CAM_RST, 1);
}

static int pulled_low(int pin)
{
	return gpio_get(pin, PULL_UP) == 0;
}

static int has_camera(void)
{
	return i2c_read16(cam_fd, 0x3c, 0x300a) == 0x56 &&
	       i2c_read16(cam_fd, 0x3c, 0x300b) == 0x40;
}

static int has_imu(void)
{
	return i2c_read8(imu_fd, 0x6a, 0x0f) == 0x6c ||
	       i2c_read8(imu_fd, 0x6b, 0x0f) == 0x6c;
}

static int has_battery(void)
{
	return adc_read(BAT_ADC) > 200;
}

int scan_modules(struct module *list)
{
	int i, n = 0;

	list[0] = (struct module){ "camera", 1, has_camera() };
	list[1] = (struct module){ "ir", 3, pulled_low(IR_TX) };
	list[2] = (struct module){ "torch", 4, pulled_low(TORCH_EN) };
	list[3] = (struct module){ "headphone", 5, pulled_low(HP_DET) };
	list[4] = (struct module){ "imu", 9, has_imu() };
	list[5] = (struct module){ "wireless", 12, uart_ping(wifi_fd) };
	list[6] = (struct module){ "screen", 14, pulled_low(SCREEN_BL) };
	list[7] = (struct module){ "battery", 21, has_battery() };
	list[8] = (struct module){ "sd card", 41, pulled_low(SD_CD) };
	list[9] = (struct module){ "audio", 44, pulled_low(AUDIO_SD) };

	for (i = 0; i < MOD_COUNT; i++)
		n += list[i].on;
	return n;
}

void save_modules(struct module *list, const char *path)
{
	FILE *f;
	int i;

	f = fopen(path, "w");
	if (!f)
		return;
	for (i = 0; i < MOD_COUNT; i++)
		fprintf(f, "%s:%d:%d\n", list[i].name, list[i].slot, list[i].on);
	fclose(f);
}
