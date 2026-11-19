#ifndef I2C_BUS_H
#define I2C_BUS_H

int i2c_open(int bus);
int i2c_read8(int fd, int addr, int reg);
int i2c_read16(int fd, int addr, int reg);

#endif
