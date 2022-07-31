# avr-i2c
I2C Library for AVR Atmega328p

![i2c](http://wiki.telink-semi.cn/tools_and_sdk/Driver/doc/kite/html/i2c_timing.png)

Example:
```
i2c_init();
i2c_addr(0x23); // 0 = success
i2c_tx_byte(0xAB); // 0 = success
i2c_uninit();
```
