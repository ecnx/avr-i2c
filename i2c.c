/* ------------------------------------------------------------------
 * I2C Library for AVR Devices
 * ------------------------------------------------------------------ */

#include "i2c.h"

/**
 * Initialize I2C Interface
 */
void i2c_init ( void )
{
    TWCR = _BV ( TWEN );
    TWBR = ( F_CPU / I2C_CONFIG_F_SCL - 16 ) / 2;
}

/**
 * Initialize I2C Interface with pullups
 */
void i2c_init_with_pullups ( void )
{
    I2C_CONFIG_DDR &= ~( _BV ( I2C_CONFIG_SDA ) | _BV ( I2C_CONFIG_SCL ) );
    I2C_CONFIG_PORT |= _BV ( I2C_CONFIG_SDA ) | _BV ( I2C_CONFIG_SCL );
    i2c_init (  );
}

/**
 * Uninitialize I2C Interface
 */
void i2c_uninit ( void )
{
    TWCR &= ~_BV ( TWEN );
}

/**
 * Wait until I2C Interface is ready
 */
static void i2c_wait ( void )
{
    while ( !( TWCR & _BV ( TWINT ) ) );
}

/**
 * Send I2C Start Condition
 */
int8_t i2c_start ( void )
{
    TWCR = _BV ( TWEN ) | _BV ( TWINT ) | _BV ( TWSTA );
    i2c_wait (  );
    return ( TWSR & TW_STATUS_MASK ) != TW_START;
}

/**
 * Send I2C Repeated-Start Condition
 */
int8_t i2c_restart ( void )
{
    TWCR = _BV ( TWEN ) | _BV ( TWINT ) | _BV ( TWSTA );
    i2c_wait (  );
    return ( TWSR & TW_STATUS_MASK ) != TW_REP_START;
}

/**
 * Send I2C Stop Condition
 */
int8_t i2c_stop ( void )
{
    TWCR = _BV ( TWEN ) | _BV ( TWINT ) | _BV ( TWSTO );
    while ( TWCR & _BV ( TWSTO ) );
    return 0;
}

/**
 * Select I2C Slave Address
 */
int8_t i2c_addr ( uint8_t addr )
{
    TWDR = addr;
    TWCR = _BV ( TWEN ) | _BV ( TWINT );
    i2c_wait (  );
    return ( TWSR & TW_STATUS_MASK ) != ( ( addr & 1 ) ? TW_MR_SLA_ACK : TW_MT_SLA_ACK );
}

/**
 * Send data byte to Slave Device
 */
int8_t i2c_tx_byte ( uint8_t byte )
{
    TWDR = byte;
    TWCR = _BV ( TWEN ) | _BV ( TWINT );
    i2c_wait (  );
    return ( TWSR & TW_STATUS_MASK ) != TW_MT_DATA_ACK;
}

/**
 * Send data bytes to Slave Device
 */
int8_t i2c_tx_data ( const uint8_t * data, size_t len )
{
    size_t i;

    for ( i = 0; i < len; i++ )
    {
        if ( i2c_tx_byte ( data[i] ) )
        {
            return 1;
        }
    }

    return 0;
}

/**
 * Receive data byte from Slave Device
 */
int8_t i2c_rx_byte ( uint8_t * byte )
{
    TWCR = _BV ( TWEN ) | _BV ( TWINT ) | _BV ( TWEA );
    i2c_wait (  );
    *byte = TWDR;
    return ( TWSR & TW_STATUS_MASK ) != TW_MR_DATA_ACK;
}

/**
 * Receive last data byte from Slave Device
 */
int8_t i2c_rx_last ( uint8_t * byte )
{
    TWCR = _BV ( TWEN ) | _BV ( TWINT );
    i2c_wait (  );
    *byte = TWDR;
    return ( TWSR & TW_STATUS_MASK ) != TW_MR_DATA_NACK;
}

/**
 * Receive data bytes from Slave Device
 */
int8_t i2c_rx_data ( uint8_t * data, size_t len )
{
    size_t i;

    for ( i = 0; i + 1 < len; i++ )
    {
        if ( i2c_rx_byte ( data + i ) )
        {
            return 1;
        }
    }

    if ( len )
    {
        if ( i2c_rx_last ( data + i ) )
        {
            return 1;
        }
    }

    return 0;
}
