#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#define PULL_NONE 0
#define PULL_UP   1
#define PULL_DOWN 2

int gpio_open(void);
int gpio_get(int pin, int pull);
int gpio_set(int pin, int val);

#endif
