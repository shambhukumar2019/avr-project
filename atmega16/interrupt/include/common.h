#ifndef COMMON_H
#define COMMON_H



#ifndef F_CPU
/**
 * @brief set clock frequency for CPU
 * 
 */
#define F_CPU 11059200UL
#endif


#define VCC     1
#define GND     0

#define SET_BIT(register,bit)       (register |= (1<<bit))
#define CLEAR_BIT(register,bit)     (register &= ~(1<<bit))



#endif