#ifndef COMMON_H
#define COMMON_H



#define VCC     1
#define GND     0

#define SET_BIT(register,bit)       (register |= (1<<bit))
#define CLEAR_BIT(register,bit)     (register &= ~(1<<bit))



#endif