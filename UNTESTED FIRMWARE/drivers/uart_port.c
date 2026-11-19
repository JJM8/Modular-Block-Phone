#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include "uart_port.h"

int uart_open(const char *path)
{
	struct termios t;
	int fd;

	fd = open(path, O_RDWR | O_NOCTTY);
	if (fd < 0)
		return -1;

	tcgetattr(fd, &t);
	cfmakeraw(&t);
	cfsetispeed(&t, B115200);
	cfsetospeed(&t, B115200);
	tcsetattr(fd, TCSANOW, &t);
	return fd;
}

int uart_ping(int fd)
{
	fd_set set;
	struct timeval tv = { 0, 200000 };
	char buf[32];

	if (fd < 0)
		return 0;

	tcflush(fd, TCIFLUSH);
	if (write(fd, "AT\r\n", 4) != 4)
		return 0;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	if (select(fd + 1, &set, NULL, NULL, &tv) <= 0)
		return 0;
	return read(fd, buf, sizeof(buf)) > 0;
}
