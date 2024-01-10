#ifndef M32_GPIO_H
#define M32_GPIO_H

#include<avr/io.h>
#include<avr/iom32.h>

#define VCC    1
#define GND    0




/*
typedef unsigned char pin;      // to store pin number
typedef unsigned char port;     // to store port name
typedef unsigned char logic;    // to store logic level (VCC/GND)
*/



/*  compiler treat it as integer,
    default pinvalue size = 4 byte

    but if we use "packed" attribute
    then pinvalue will use least size needed.
    __attribute__ ((__packed__))
*/
/*
typedef enum
{
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8
}pinvalue;
*/



/*
    store variables for pin number,
    port number and logic level set.

    to minimize space required bitfields are used.

    only 2 byte space will be occupied.

    further thinking required...
*/
/*
typedef struct
{
    uint8_t port    :8;
    uint8_t pin     :4;
    uint8_t logic   :1;
}gpio_config;
*/



/*     ---functions discription---

    param1 -> store pin value
    param2 -> store port name
    paran3 -> store logic level (VCC/GND)

    return -> void

    apply to all below functions
*/
// set given pin of a port as output
void gpio_setout(uint8_t,uint8_t);

// set given pin of a port as input
void gpio_setin(uint8_t,uint8_t);


// set given logic level of a given pin of a port
// param3 -> VCC/GND
void gpio_set_output(uint8_t,uint8_t,uint8_t);

// turn on pullup of given pin
void gpio_pullup_on(uint8_t,uint8_t);

// turn off pullup of given pin
void gpio_pullup_off(uint8_t,uint8_t);

// disable pullup of all ports
// return -> void
// param -> null
void gpio_pullup_disable(void);

// enable pullup of all ports
// return -> void
// param -> null
void gpio_pullup_enable(void);

// read a given pin on given port
// return -> read pin logic level (VCC/GND)
volatile uint8_t gpio_read(uint8_t,uint8_t);





#endif