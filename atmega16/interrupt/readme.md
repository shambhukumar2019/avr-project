@ this project contains device driver for atmega16 interrupt handling.


@ Atmega32 and Atmega16

***     total 21 interrupts     ***

-> three external interrupts (INT2,INT1,INT0)

-> timer interrupts

-> uart interrupts

-> spi interrupt

-> eeprom interrupt

-> adc interrupt

-> store program memory interrupt

-> reset interrupt

-> analog comparator interrupt



@ Interrupt with lowest address has highest priority

@ Interrupt priority cannot be changed

@ RESET has highest priority

@ Store Program Memory has lowest priority