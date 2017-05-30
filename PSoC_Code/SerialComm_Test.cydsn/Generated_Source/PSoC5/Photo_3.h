/*******************************************************************************
* File Name: Photo_3.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Photo_3_H) /* Pins Photo_3_H */
#define CY_PINS_Photo_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Photo_3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Photo_3__PORT == 15 && ((Photo_3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Photo_3_Write(uint8 value);
void    Photo_3_SetDriveMode(uint8 mode);
uint8   Photo_3_ReadDataReg(void);
uint8   Photo_3_Read(void);
void    Photo_3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Photo_3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Photo_3_SetDriveMode() function.
     *  @{
     */
        #define Photo_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Photo_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Photo_3_DM_RES_UP          PIN_DM_RES_UP
        #define Photo_3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Photo_3_DM_OD_LO           PIN_DM_OD_LO
        #define Photo_3_DM_OD_HI           PIN_DM_OD_HI
        #define Photo_3_DM_STRONG          PIN_DM_STRONG
        #define Photo_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Photo_3_MASK               Photo_3__MASK
#define Photo_3_SHIFT              Photo_3__SHIFT
#define Photo_3_WIDTH              1u

/* Interrupt constants */
#if defined(Photo_3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Photo_3_SetInterruptMode() function.
     *  @{
     */
        #define Photo_3_INTR_NONE      (uint16)(0x0000u)
        #define Photo_3_INTR_RISING    (uint16)(0x0001u)
        #define Photo_3_INTR_FALLING   (uint16)(0x0002u)
        #define Photo_3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Photo_3_INTR_MASK      (0x01u) 
#endif /* (Photo_3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Photo_3_PS                     (* (reg8 *) Photo_3__PS)
/* Data Register */
#define Photo_3_DR                     (* (reg8 *) Photo_3__DR)
/* Port Number */
#define Photo_3_PRT_NUM                (* (reg8 *) Photo_3__PRT) 
/* Connect to Analog Globals */                                                  
#define Photo_3_AG                     (* (reg8 *) Photo_3__AG)                       
/* Analog MUX bux enable */
#define Photo_3_AMUX                   (* (reg8 *) Photo_3__AMUX) 
/* Bidirectional Enable */                                                        
#define Photo_3_BIE                    (* (reg8 *) Photo_3__BIE)
/* Bit-mask for Aliased Register Access */
#define Photo_3_BIT_MASK               (* (reg8 *) Photo_3__BIT_MASK)
/* Bypass Enable */
#define Photo_3_BYP                    (* (reg8 *) Photo_3__BYP)
/* Port wide control signals */                                                   
#define Photo_3_CTL                    (* (reg8 *) Photo_3__CTL)
/* Drive Modes */
#define Photo_3_DM0                    (* (reg8 *) Photo_3__DM0) 
#define Photo_3_DM1                    (* (reg8 *) Photo_3__DM1)
#define Photo_3_DM2                    (* (reg8 *) Photo_3__DM2) 
/* Input Buffer Disable Override */
#define Photo_3_INP_DIS                (* (reg8 *) Photo_3__INP_DIS)
/* LCD Common or Segment Drive */
#define Photo_3_LCD_COM_SEG            (* (reg8 *) Photo_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Photo_3_LCD_EN                 (* (reg8 *) Photo_3__LCD_EN)
/* Slew Rate Control */
#define Photo_3_SLW                    (* (reg8 *) Photo_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Photo_3_PRTDSI__CAPS_SEL       (* (reg8 *) Photo_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Photo_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Photo_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Photo_3_PRTDSI__OE_SEL0        (* (reg8 *) Photo_3__PRTDSI__OE_SEL0) 
#define Photo_3_PRTDSI__OE_SEL1        (* (reg8 *) Photo_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Photo_3_PRTDSI__OUT_SEL0       (* (reg8 *) Photo_3__PRTDSI__OUT_SEL0) 
#define Photo_3_PRTDSI__OUT_SEL1       (* (reg8 *) Photo_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Photo_3_PRTDSI__SYNC_OUT       (* (reg8 *) Photo_3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Photo_3__SIO_CFG)
    #define Photo_3_SIO_HYST_EN        (* (reg8 *) Photo_3__SIO_HYST_EN)
    #define Photo_3_SIO_REG_HIFREQ     (* (reg8 *) Photo_3__SIO_REG_HIFREQ)
    #define Photo_3_SIO_CFG            (* (reg8 *) Photo_3__SIO_CFG)
    #define Photo_3_SIO_DIFF           (* (reg8 *) Photo_3__SIO_DIFF)
#endif /* (Photo_3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Photo_3__INTSTAT)
    #define Photo_3_INTSTAT            (* (reg8 *) Photo_3__INTSTAT)
    #define Photo_3_SNAP               (* (reg8 *) Photo_3__SNAP)
    
	#define Photo_3_0_INTTYPE_REG 		(* (reg8 *) Photo_3__0__INTTYPE)
#endif /* (Photo_3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Photo_3_H */


/* [] END OF FILE */
