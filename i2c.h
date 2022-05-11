/* ------------------------------------------------------------------
 * I2C Library for AVR Devices
 * ------------------------------------------------------------------ */

#ifndef I2C_LIBRARY_H
#define I2C_LIBRARY_H

#include <stdint.h>
#include <util/twi.h>
#include <avr/io.h>
#include <stddef.h>

/**
 * I2C Library Configuration
 */
#define I2C_CONFIG_F_SCL 100000
#define I2C_CONFIG_DDR DDRC
#define I2C_CONFIG_PORT PORTC
#define I2C_CONFIG_SDA PC4
#define I2C_CONFIG_SCL PC5

/**
 * Initialize I2C Interface
 */
extern void i2c_init ( void );

/**
 * Initialize I2C Interface with pullups
 */
extern void i2c_init_with_pullups ( void );

/**
 * Uninitialize I2C Interface
 */
extern void i2c_uninit ( void );

/**
 * Send I2C Start Condition
 */
extern int8_t i2c_start ( void );

/**
 * Send I2C Repeated-Start Condition
 */
extern int8_t i2c_restart ( void );

/**
 * Send I2C Stop Condition
 */
extern int8_t i2c_stop ( void );

/**
 * Select I2C Slave Address
 */
extern int8_t i2c_addr ( uint8_t addr );

/**
 * Send data byte to Slave Device
 */
extern int8_t i2c_tx_byte ( uint8_t byte );

/**
 * Send data bytes to Slave Device
 */
extern int8_t i2c_tx_data ( const uint8_t * data, size_t len );

/**
 * Receive data byte from Slave Device
 */
extern int8_t i2c_rx_byte ( uint8_t * byte );

/**
 * Receive last data byte from Slave Device
 */
extern int8_t i2c_rx_last ( uint8_t * byte );

/**
 * Receive data bytes from Slave Device
 */
extern int8_t i2c_rx_data ( uint8_t * data, size_t len );

#endif
