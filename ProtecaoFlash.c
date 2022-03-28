#include <ProtecaoFlash.h>
#include "stm32f1xx.h"

static HAL_StatusTypeDef EscreverBitsRDP(uint8_t ReadProtectLevel);

/**************************************************************************************************************************************************/
/*                                                                                                                                                */
/* @resumo:   : Bloqueia a leitura dos dados contidos na memória FLASH do microcontrolador.										 				  */
/*				OBS: Se a proteção de leitura estiver configurada enquanto o depurador ainda estiver conectado através de JTAG/SWD, aplique um	  */
/* 				POR (power-on reset) em vez de um system reset (sem conexão do depurador).														  */
/* @param1    : void                                                                              												  */
/* @ret val   : void 																															  */
/*                                                                                                                                                */
/**************************************************************************************************************************************************/
void BloquearLeituraDaFlash(void){
	if (LerBitsRDP() == RDP_LEVEL_0){
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		EscreverBitsRDP(RDP_LEVEL_1);
		HAL_FLASH_OB_Launch();
	}
}
/**************************************************************************************************************************************************/


/**************************************************************************************************************************************************/
/*                                                                                                                                                */
/* @resumo:   : Desbloqueia a leitura dos dados contidos na memória FLASH do microcontrolador.											 		  */
/*				OBS: Esta operação primeiro força um apagamento em massa da memória Flash. 														  */
/* @param1    : void                                                                              												  */
/* @ret val   : void 																															  */
/*                                                                                                                                                */
/**************************************************************************************************************************************************/
void DesbloquearLeituraDaFlash(void){
	if (LerBitsRDP() == RDP_LEVEL_1){
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		EscreverBitsRDP(RDP_LEVEL_0);
	  	HAL_FLASH_OB_Launch();
	}
}
/**************************************************************************************************************************************************/


/**************************************************************************************************************************************************/
/*                                                                                                                                                */
/* @resumo:   : Escreve valor de nível de proteção de leitura da memória FLASH nos bits RDP												 		  */
/* @param1    : Valor de proteção que deverá ser escrito em RDP		                            												  */
/* @ret val   : HAL status 																														  */
/*                                                                                                                                                */
/**************************************************************************************************************************************************/
static HAL_StatusTypeDef EscreverBitsRDP(uint8_t ReadProtectLevel){
	HAL_StatusTypeDef status = HAL_OK;

	/* Check the parameters */
	assert_param(IS_OB_RDP_LEVEL(ReadProtectLevel));

	/* Wait for last operation to be completed */
	status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

	if(status == HAL_OK){
		/* If the previous operation is completed, proceed to erase the option bytes */
		SET_BIT(FLASH->CR, FLASH_CR_OPTER);
		SET_BIT(FLASH->CR, FLASH_CR_STRT);

		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

		/* If the erase operation is completed, disable the OPTER Bit */
		CLEAR_BIT(FLASH->CR, FLASH_CR_OPTER);

		if(status == HAL_OK){
			/* Enable the Option Bytes Programming operation */
			SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

			WRITE_REG(OB->RDP, ReadProtectLevel);

			/* Wait for last operation to be completed */
			status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

			/* if the program operation is completed, disable the OPTPG Bit */
			CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
		}
	}
	return status;
}
/**************************************************************************************************************************************************/


/**************************************************************************************************************************************************/
/*                                                                                                                                                */
/* @resumo:   : Le o valor de nível de proteção de leitura da memória FLASH nos bits RDP  												 		  */
/* @param1    : void		   											                         												  */
/* @ret val   : Nível de proteção de leitura da memória FLASH																					  */
/*                                                                                                                                                */
/**************************************************************************************************************************************************/
uint8_t LerBitsRDP(void)
{
	uint32_t readstatus = RDP_LEVEL_0;
	uint32_t tmp_reg = 0U;

	/* Read RDP level bits */
	tmp_reg = READ_BIT(FLASH->OBR, FLASH_OBR_RDPRT);

	if (tmp_reg == FLASH_OBR_RDPRT){
		readstatus = RDP_LEVEL_1;
	}
	else{
		readstatus = RDP_LEVEL_0;
	}
	return readstatus;
}
/**************************************************************************************************************************************************/
