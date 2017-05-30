/*******************************************************************************
* File Name: Photo_4.h  
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

#if !defined(CY_PINS_Photo_4_H) /* Pins Photo_4_H */
#define CY_PINS_Photo_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Photo_4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Photo_4__PORT == 15 && ((Photo_4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Photo_4_Write(uint8 value);
void    Photo_4_SetDriveMode(uint8 mode);
uint8   Photo_4_ReadDataReg(void);
uint8   Photo_4_Read(void);
void    Photo_4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Photo_4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Photo_4_SetDriveMode() function.
     *  @{
     */
        #define Photo_4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Photo_4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Photo_4_DM_RES_UP          PIN_DM_RES_UP
        #define Photo_4_DM_RES_DWN         PIN_DM_RES_DWN
        #define Photo_4_DM_OD_LO           PIN_DM_OD_LO
        #define Photo_4_DM_OD_HI           PIN_DM_OD_HI
        #define Photo_4_DM_STRONG          PIN_DM_STRONG
        #define Photo_4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Photo_4_MASK               Photo_4__MASK
#define Photo_4_SHIFT              Photo_4__SHIFT
#define Photo_4_WIDTH              1u

/* Interrupt constants */
#if defined(Photo_4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Photo_4_SetInterruptMode() function.
     *  @{
     */
        #define Photo_4_INTR_NONE      (uint16)(0x0000u)
        #define Photo_4_INTR_RISING    (uint16)(0x0001u)
        #define Photo_4_INTR_FALLING   (uint16)(0x0002u)
        #define Photo_4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Photo_4_INTR_MASK      (0x01u) 
#endif /* (Photo_4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Photo_4_PS                     (* (reg8 *) Photo_4__PS)
/* Data Register */
#define Photo_4_DR                     (* (reg8 *) Photo_4__DR)
/* Port Number */
#define Photo_4_PRT_NUM                (* (reg8 *) Photo_4__PRT) 
/* Connect to Analog Globals */                                                  
#define Photo_4_AG                     (* (reg8 *) Photo_4__AG)                       
/* Analog MUX bux enable */
#define Photo_4_AMUX                   (* (reg8 *) Photo_4__AMUX) 
/* Bidirectional Enable */                                                        
#define Photo_4_BIE                    (* (reg8 *) Photo_4__BIE)
/* Bit-mask for Aliased Register Access */
#define Photo_4_BIT_MASK               (* (reg8 *) Photo_4__BIT_MASK)
/* Bypass Enable */
#define Photo_4_BYP                    (* (reg8 *) Photo_4__BYP)
/* Port wide control signals */                                                   
#define Photo_4_CTL                    (* (reg8 *) Photo_4__CTL)
/* Drive Modes */
#define Photo_4_DM0                    (* (reg8 *) Photo_4__DM0) 
#define Photo_4_DM1                    (* (reg8 *) Photo_4__DM1)
#define Photo_4_DM2                    (* (reg8 *) Photo_4__DM2) 
/* Input Buffer Disable Override */
#define Photo_4_INP_DIS                (* (reg8 *) Photo_4__INP_DIS)
/* LCD Common or Segment Drive */
#define Photo_4_LCD_COM_SEG            (* (reg8 *) Photo_4__LCD_COM_SEG)
/* Enable Segment LCD */
#define Photo_4_LCD_EN                 (* (reg8 *) Photo_4__LCD_EN)
/* Slew Rate Control */
#define Photo_4_SLW                    (* (reg8 *) Photo_4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Photo_4_PRTDSI__CAPS_SEL       (* (reg8 *) Photo_4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Photo_4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Photo_4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Photo_4_PRTDSI__OE_SEL0        (* (reg8 *) Photo_4__PRTDSI__OE_SEL0) 
#define Photo_4_PRTDSI__OE_SEL1        (* (reg8 *) Photo_4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Photo_4_PRTDSI__OUT_SEL0       (* (reg8 *) Photo_4__PRTDSI__OUT_SEL0) 
#define Photo_4_PRTDSI__OUT_SEL1       (* (reg8 *) Photo_4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Photo_4_PRTDSI__SYNC_OUT       (* (reg8 *) Photo_4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Photo_4__SIO_CFG)
    #define Photo_4_SIO_HYST_EN        (* (reg8 *) Photo_4__SIO_HYST_EN)
    #define Photo_4_SIO_REG_HIFREQ     (* (reg8 *) Photo_4__SIO_REG_HIFREQ)
    #define Photo_4_SIO_CFG            (* (reg8 *) Photo_4__SIO_CFG)
    #define Photo_4_SIO_DIFF           (* (reg8 *) Photo_4__SIO_DIFF)
#endif /* (Photo_4__SIO_CFG) */

/* Interrupt Registers */
#if defined(Photo_4__INTSTAT)
    #define Photo_4_INTSTAT            (* (reg8 *) Photo_4__INTSTAT)
    #define Photo_4_SNAP               (* (reg8 *) Photo_4__SNAP)
    
	#define Photo_4_0_INTTYPE_REG 		(* (reg8 *) Photo_4__0__INTTYPE)
#endif /* (Photo_4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Photo_4_H */


/* [] END OF FILE */
