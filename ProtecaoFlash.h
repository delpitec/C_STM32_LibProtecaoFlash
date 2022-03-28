/*
 * FlashLock.h
 *
 *  Created on: 15 de mar de 2022
 *      Author: Rafael
 */

#include <stdint.h>

#ifndef INC_PROTECAOFLASH_H_
#define INC_PROTECAOFLASH_H_

#define RDP_LEVEL_0            ((uint8_t)0xA5)  // No protection
#define RDP_LEVEL_1            ((uint8_t)0x00)  // Protected

void BloquearLeituraDaFlash(void);
void DesbloquearLeituraDaFlash(void);
uint8_t LerBitsRDP(void);

#endif /* INC_PROTECAOFLASH_H_ */
