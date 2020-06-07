/*
 * DEI.h
 *
 * Created: 2/18/2020 11:37:05 PM
 *  Author: Reem
 */ 


#ifndef DEI_H_
#define DEI_H_
#include "..\Common\common_macros.h"
#include "..\Common\Error_handling.h"
#include "interrupt.h"
#include "registers.h"

/******************************************/
/*               Defines                  */
/******************************************/

#define _DEI_INT0                    0
#define _DEI_INT1                    1
#define _DEI_INT2                    2

#define DEI_MODE_RISING             (0)
#define DEI_MODE_FALLING            (1)
#define DEI_MODE_BOTH               (2)
    


/******************************************/
/*             FUNCTION PROTYPES          */
/******************************************/

/*
 * Fun----------: ERROR_STATUS DEI_Init(uint8_t DEI_Ch);
 * Input--------: digital external interrupt channel
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: initializes the DEI_Channel 
*/
extern ERROR_STATUS DEI_Init(uint8_t DEI_Channel);
extern ERROR_STATUS DEI_setMode(uint8_t DEI_Channel,uint8_t DEI_Mode,void (*DEI_CBK)(void));


#endif /* DEI_H_ */