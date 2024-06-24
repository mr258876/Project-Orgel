#ifndef _PINOUTS_H_
#define _PINOUTS_H_

#if defined(ESP_PLATFORM)

#define MOTOR_ENABLE_Pin 33
#define MOTOR_SERIAL_RX_Pin 16
#define MOTOR_SERIAL_TX_Pin 17

#define DISPLAY_I2C_RST_Pin 255     // 255 == U8X8_PIN_NONE (keep default)
#define DISPLAY_I2C_SCL_Pin 255     // 255 == U8X8_PIN_NONE (keep default)
#define DISPLAY_I2C_SDA_Pin 255     // 255 == U8X8_PIN_NONE (keep default)

#define ENCODER_A_Pin 34
#define ENCODER_B_Pin 35
#define ENCODER_OK_Pin 32

#elif defined(NRF51)

#define MOTOR_ENABLE_Pin 16
#define MOTOR_SERIAL_RX_Pin 8
#define MOTOR_SERIAL_TX_Pin 9

#define DISPLAY_I2C_RST_Pin 255     // 255 == U8X8_PIN_NONE (keep default)
#define DISPLAY_I2C_SCL_Pin 24
#define DISPLAY_I2C_SDA_Pin 25

#define ENCODER_A_Pin 23
#define ENCODER_B_Pin 22
#define ENCODER_OK_Pin 21

#endif

#endif