/*******************************************************************************
* File Name: Sw_Mode.h  
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

#if !defined(CY_PINS_Sw_Mode_H) /* Pins Sw_Mode_H */
#define CY_PINS_Sw_Mode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sw_Mode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Sw_Mode__PORT == 15 && ((Sw_Mode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Sw_Mode_Write(uint8 value);
void    Sw_Mode_SetDriveMode(uint8 mode);
uint8   Sw_Mode_ReadDataReg(void);
uint8   Sw_Mode_Read(void);
void    Sw_Mode_SetInterruptMode(uint16 position, uint16 mode);
uint8   Sw_Mode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Sw_Mode_SetDriveMode() function.
     *  @{
     */
        #define Sw_Mode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Sw_Mode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Sw_Mode_DM_RES_UP          PIN_DM_RES_UP
        #define Sw_Mode_DM_RES_DWN         PIN_DM_RES_DWN
        #define Sw_Mode_DM_OD_LO           PIN_DM_OD_LO
        #define Sw_Mode_DM_OD_HI           PIN_DM_OD_HI
        #define Sw_Mode_DM_STRONG          PIN_DM_STRONG
        #define Sw_Mode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Sw_Mode_MASK               Sw_Mode__MASK
#define Sw_Mode_SHIFT              Sw_Mode__SHIFT
#define Sw_Mode_WIDTH              1u

/* Interrupt constants */
#if defined(Sw_Mode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Sw_Mode_SetInterruptMode() function.
     *  @{
     */
        #define Sw_Mode_INTR_NONE      (uint16)(0x0000u)
        #define Sw_Mode_INTR_RISING    (uint16)(0x0001u)
        #define Sw_Mode_INTR_FALLING   (uint16)(0x0002u)
        #define Sw_Mode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Sw_Mode_INTR_MASK      (0x01u) 
#endif /* (Sw_Mode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sw_Mode_PS                     (* (reg8 *) Sw_Mode__PS)
/* Data Register */
#define Sw_Mode_DR                     (* (reg8 *) Sw_Mode__DR)
/* Port Number */
#define Sw_Mode_PRT_NUM                (* (reg8 *) Sw_Mode__PRT) 
/* Connect to Analog Globals */                                                  
#define Sw_Mode_AG                     (* (reg8 *) Sw_Mode__AG)                       
/* Analog MUX bux enable */
#define Sw_Mode_AMUX                   (* (reg8 *) Sw_Mode__AMUX) 
/* Bidirectional Enable */                                                        
#define Sw_Mode_BIE                    (* (reg8 *) Sw_Mode__BIE)
/* Bit-mask for Aliased Register Access */
#define Sw_Mode_BIT_MASK               (* (reg8 *) Sw_Mode__BIT_MASK)
/* Bypass Enable */
#define Sw_Mode_BYP                    (* (reg8 *) Sw_Mode__BYP)
/* Port wide control signals */                                                   
#define Sw_Mode_CTL                    (* (reg8 *) Sw_Mode__CTL)
/* Drive Modes */
#define Sw_Mode_DM0                    (* (reg8 *) Sw_Mode__DM0) 
#define Sw_Mode_DM1                    (* (reg8 *) Sw_Mode__DM1)
#define Sw_Mode_DM2                    (* (reg8 *) Sw_Mode__DM2) 
/* Input Buffer Disable Override */
#define Sw_Mode_INP_DIS                (* (reg8 *) Sw_Mode__INP_DIS)
/* LCD Common or Segment Drive */
#define Sw_Mode_LCD_COM_SEG            (* (reg8 *) Sw_Mode__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sw_Mode_LCD_EN                 (* (reg8 *) Sw_Mode__LCD_EN)
/* Slew Rate Control */
#define Sw_Mode_SLW                    (* (reg8 *) Sw_Mode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sw_Mode_PRTDSI__CAPS_SEL       (* (reg8 *) Sw_Mode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sw_Mode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sw_Mode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sw_Mode_PRTDSI__OE_SEL0        (* (reg8 *) Sw_Mode__PRTDSI__OE_SEL0) 
#define Sw_Mode_PRTDSI__OE_SEL1        (* (reg8 *) Sw_Mode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sw_Mode_PRTDSI__OUT_SEL0       (* (reg8 *) Sw_Mode__PRTDSI__OUT_SEL0) 
#define Sw_Mode_PRTDSI__OUT_SEL1       (* (reg8 *) Sw_Mode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sw_Mode_PRTDSI__SYNC_OUT       (* (reg8 *) Sw_Mode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Sw_Mode__SIO_CFG)
    #define Sw_Mode_SIO_HYST_EN        (* (reg8 *) Sw_Mode__SIO_HYST_EN)
    #define Sw_Mode_SIO_REG_HIFREQ     (* (reg8 *) Sw_Mode__SIO_REG_HIFREQ)
    #define Sw_Mode_SIO_CFG            (* (reg8 *) Sw_Mode__SIO_CFG)
    #define Sw_Mode_SIO_DIFF           (* (reg8 *) Sw_Mode__SIO_DIFF)
#endif /* (Sw_Mode__SIO_CFG) */

/* Interrupt Registers */
#if defined(Sw_Mode__INTSTAT)
    #define Sw_Mode_INTSTAT            (* (reg8 *) Sw_Mode__INTSTAT)
    #define Sw_Mode_SNAP               (* (reg8 *) Sw_Mode__SNAP)
    
	#define Sw_Mode_0_INTTYPE_REG 		(* (reg8 *) Sw_Mode__0__INTTYPE)
#endif /* (Sw_Mode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Sw_Mode_H */


/* [] END OF FILE */
