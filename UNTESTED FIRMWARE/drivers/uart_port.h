#ifndef UART_PORT_H
#define UART_PORT_H

int uart_open(const char *path);
int uart_ping(int fd);

#endif
