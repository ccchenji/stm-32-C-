#ifndef __scan_H
#define	__scan_H

#include "stm32f10x.h"
#define mm_ON  1
#define mm_OFF 0

void mm_scan_GPIO_Config(void);
u8 mm_scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __scan_H */
