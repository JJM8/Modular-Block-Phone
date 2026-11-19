CROSS ?= arm-linux-gnueabihf-
CC = $(CROSS)gcc
CFLAGS = -O2 -Wall

src = main/main.c drivers/gpio_pin.c drivers/i2c_bus.c drivers/adc_read.c \
      drivers/uart_port.c drivers/fb_screen.c drivers/font_5x7.c \
      drivers/touch_input.c drivers/module_scan.c

mbp_gui: $(src)
	$(CC) $(CFLAGS) -o $@ $(src)

install: mbp_gui
	mkdir -p $(DESTDIR)/root/mbp
	cp mbp_gui $(DESTDIR)/root/mbp/
	cp -r apps $(DESTDIR)/root/mbp/

clean:
	rm -f mbp_gui
