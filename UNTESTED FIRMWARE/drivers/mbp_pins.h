#ifndef MBP_PINS_H
#define MBP_PINS_H

#define PIN(bank, n) (((bank) - 'A') * 32 + (n))

#define BUT_UP      PIN('B', 2)
#define BUT_DOWN    PIN('B', 3)
#define AUDIO_SD    PIN('B', 4)
#define SCREEN_BL   PIN('B', 6)
#define CAM_RST     PIN('D', 15)
#define CAM_PWDN    PIN('D', 17)
#define SD_CD       PIN('E', 12)
#define HP_DET      PIN('E', 13)
#define TORCH_EN    PIN('F', 6)
#define IR_TX       PIN('G', 10)

#define CAM_BUS     2
#define IMU_BUS     1
#define WIFI_UART   "/dev/ttyS1"
#define BAT_ADC     "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"

#endif
