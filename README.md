# UART_Communication_with_I2C_LCD_Menu


In this project i have ArduinoJSON for UART communication from Tx to Rx.


**UART_TX_with_I2C_LCD_Menu_&_JSON:-**
I am storing all the values in the EEPROM.
Dynamically i am changing the led1 brightness and led2 ON/OFF state by using the I2C LCD menu.
After selecting the values from the menu, we are saving in the EEPROM and when the device is restarted the values is automatically sending to the receiver MCU via UART communication protocol.


1. BTN1 = 3
2. BTN2 = 5
3. BTN3 = 7
4. LED1 = 10
5. LED2 = 2
6. SDA = A4
7. SCL = A5



**UART_RX_&_JSON:-**
After receiving the values from the transmitter MCU again we are storing the values in the EEPROM.

1. LED1 = 23
2. LED2 = 13
