#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c_bus.h"

int i2c_open(int bus)
{
	char path[20];

	snprintf(path, sizeof(path), "/dev/i2c-%d", bus);
	return open(path, O_RDWR);
}

static int read_reg(int fd, int addr, unsigned char *reg, int reg_len)
{
	unsigned char val;
	struct i2c_msg msgs[2];
	struct i2c_rdwr_ioctl_data xfer;

	msgs[0].addr = addr;
	msgs[0].flags = 0;
	msgs[0].len = reg_len;
	msgs[0].buf = reg;
	msgs[1].addr = addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = 1;
	msgs[1].buf = &val;
	xfer.msgs = msgs;
	xfer.nmsgs = 2;

	if (fd < 0 || ioctl(fd, I2C_RDWR, &xfer) < 0)
		return -1;
	return val;
}

int i2c_read8(int fd, int addr, int reg)
{
	unsigned char r = reg;

	return read_reg(fd, addr, &r, 1);
}

int i2c_read16(int fd, int addr, int reg)
{
	unsigned char r[2] = { reg >> 8, reg & 0xff };

	return read_reg(fd, addr, r, 2);
}
