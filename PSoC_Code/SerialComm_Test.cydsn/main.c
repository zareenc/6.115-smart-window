/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <cyapicallbacks.h>
#include <project.h>

// Functions
int readPot();
void sendPWM(int);
void printPWM();
int readPhotoresistor();
int getAvgPhotoresistors();
void printPhotoresistor(int, int);
void pushPhotoBuffer(int);
int averagePhotoBuffer();
int getPhotoPWMDiff(int, int);
int calcNewPWM(int, int);
int getPhotoDiff(int, int);
//int getCurrentPWM();
//int autoMode(int, int); 


// Global variables 

// states
int ledState;
int userMode;       // 0 = manual mode, 1 = automated mode, 2 = init timer mode, 3 = timer mode

// pwm
uint8 currentPWM; 
int receivedPWM = 0;
int initPWM;

// photoresistors
int currentPhoto;
int initPhoto;
int timeAvgPhoto;
int bufferLength = 10;
int photoBuffer[10];
int photoPWMDiff;

// timing
int timeMode = 0;
int timePrefsLength = 3;
int timePrefs[3] = {255, 250, 245};
int timeInterval = 20;
int timeCounter = 0;

// led
int ledPWM = 0;
int ledPWMState = 0;    // 0 = stopped, 1 = started

// constants
uint8 GET_CURRENT_PWM = 1;
int const MANUAL_MODE = 0;
int const AUTO_MODE = 1;
int const INIT_TIMED_MODE = 2;
int const TIMED_MODE = 3;

int const DAWN = 0;
int const MORNING = 1;
int const AFTERNOON = 2;
int const EVENING = 3;

int const LIGHTING_ON = 1;
int const LIGHTING_OFF = 0;

/* Interrupts */ 

// Switch interrupt
/*
CY_ISR(SW_INT)
{
    userMode = !userMode;
    LED_Mode_Write(userMode);
    
    if (userMode == AUTO_MODE)
    {
        AMux_1_Select(0);
        initPWM = readPot();
        LCD_Char_1_Position(1, 5);
        LCD_Char_1_PrintNumber(initPWM);

        AMux_1_Select(1);
        CyDelay(100);
        initPhoto = readPhotoresistor();
        //initPhoto = 3700;
        LCD_Char_1_Position(0, 12);
  	    LCD_Char_1_PrintNumber(initPhoto);
    }
    else if (userMode == MANUAL_MODE)
    {
        AMux_1_Select(0);        
    }
    //LCD_Char_1_Position(1, 11);
    //LCD_Char_1_PrintNumber(userMode);
}*/

// Tx interrupt
/*CY_ISR(TX_INT)
{
    if (state == 0) {
        Pin_2_Write(1);
        state = 1;
    }
    else if (state == 1) {
        Pin_2_Write(0);
        state = 0;
    }
}*/

// Timer interrupt
CY_ISR(TIMER_INT)
{
    Timer_1_STATUS;         // clear interrupt flag 
    LED_Write(!LED_Read());
    timeCounter += 1;
    if ((userMode == TIMED_MODE) && (timeCounter == timeInterval))
    {
        int done = 0;
        timeCounter = 0;    // reset counter 
        
        // set state and corresponding PWM 
        if (timeMode == DAWN)
        {
            timeMode = MORNING;   
            currentPWM = timePrefs[0];
            done = 1;
        }
        else if (!done && timeMode == MORNING)
        {
            LED_Mode_Write(1);
            timeMode = AFTERNOON;   
            currentPWM = timePrefs[1];
            done = 1;
        }
        else if (!done && timeMode == AFTERNOON)
        {
            LED_Mode_Write(0);
            timeMode = EVENING;   
            currentPWM = timePrefs[2];
            done = 1;
        }
        else if (!done && timeMode == EVENING)
        {
            timeMode = DAWN; 
            userMode = MANUAL_MODE;
            Timer_1_Stop();
            done = 1;
        }
        
        // send PWM 
        sendPWM(currentPWM);
        printPWM();
        
        // reset reference PWM and photoresistor reading
        initPWM = currentPWM;
    }
}

// Rx interrupt 
CY_ISR(RX_INT)
{
    //currentPWM = UART_1_ReadRxData();
    //receivedPWM = 1;
    uint8 amuletData = UART_1_ReadRxData();

    // Set manual mode
    if ((amuletData == 0x31) && (userMode != MANUAL_MODE))
    {
        if (userMode != TIMED_MODE)
        {
            userMode = MANUAL_MODE;
            LED_Mode_Write(userMode);
            PWM_1_Stop(); 
        }
    }
    
    // Set automated mode
    else if ((amuletData == 0x32) && (userMode != AUTO_MODE))
    {
        PWM_1_Stop(); 
        userMode = AUTO_MODE;   
        LED_Mode_Write(userMode);
        
        // Initialize PWM
        initPWM = currentPWM;

        // Get current photoresistor reading
        initPhoto = timeAvgPhoto;
        
        // Get difference
        /*photoPWMDiff = getPhotoPWMDiff(initPhoto, initPWM);
        printPWM();*/
        
        // Initialize time buffer with current photoresistor reading 
        /*int i;
        for (i=0; i<bufferLength; i+=1)
        {
            pushPhotoBuffer(currentPhoto);
        }
        timeAvgPhoto = averagePhotoBuffer();
        printPhotoresistor(currentPhoto, timeAvgPhoto);*/
    }
    
    // Adjust current brightness in manual mode or in simulation 
    else if ((userMode == MANUAL_MODE || userMode == TIMED_MODE) && 
            (amuletData <= 255) && (amuletData >= 245)) // can manually adjust in simulation
    {
        currentPWM = amuletData;
        printPWM();
        sendPWM(currentPWM);
        if (userMode == TIMED_MODE)
        {
            initPWM = currentPWM;   
        }
    }
    
    // Set timed initialization mode 
    else if ((amuletData == 0x41) && (userMode != INIT_TIMED_MODE) && (userMode != TIMED_MODE)) // can't adjust if running simulation
    {
        userMode = INIT_TIMED_MODE;
        PWM_1_Stop(); 
    }
    
    // Adjust brightness in morning adjust mode 
    else if ((userMode == INIT_TIMED_MODE) && (amuletData <= 0xef) && (amuletData >=0xe5))
    {
        int brightnessVal = (amuletData | 0xf0);
        timePrefs[0] = brightnessVal;
        currentPWM = brightnessVal;
        printPWM();
        sendPWM(currentPWM);
    }

    // Adjust brightness in afternoon adjust mode 
    else if ((userMode == INIT_TIMED_MODE) && (amuletData <= 0xdf) && (amuletData >=0xd5))
    {
        int brightnessVal = (amuletData | 0xf0);
        timePrefs[1] = brightnessVal;
        currentPWM = brightnessVal;
        printPWM();
        sendPWM(currentPWM);
    }

    // Adjust brightness in evening adjust mode 
    else if ((userMode == INIT_TIMED_MODE) && (amuletData <= 0xcf) && (amuletData >=0xc5))
    {
        int brightnessVal = (amuletData | 0xf0);
        timePrefs[2] = brightnessVal;
        currentPWM = brightnessVal;
        printPWM();
        sendPWM(currentPWM);
    }
    
    // Start simulation in timed mode
    else if ((amuletData == 0x42) && (userMode != TIMED_MODE))
    {
        // set mode
        userMode = TIMED_MODE;
        timeCounter = 0;
        timeMode = MORNING;
        
        // set initial PWM 
        currentPWM = timePrefs[0];
        printPWM();
        
        // set reference PWM and photoresistor reading
        initPWM = currentPWM;
        initPhoto = timeAvgPhoto;
        
        PWM_1_Stop(); 
        
        // start timer
        Timer_1_Start();
        LED_Mode_Write(0);
    }
}

void main()
{
    // Initialize LCD
	LCD_Char_1_Start();		
	LCD_Char_1_ClearDisplay();
    LCD_Char_1_PrintString("Photo: ");
    LCD_Char_1_Position(1, 0);
    LCD_Char_1_PrintString("PWM: ");
    /*LCD_Char_1_Position(1, 0);
    LCD_Char_1_PrintString("User Mode: ");*/
	
    // Initialize analog mux and ADC
    AMux_1_Init();
    AMux_1_Start();
    //AMux_1_Select(0);
	ADC_DelSig_1_Start();				// start the ADC_DelSig_1
	ADC_DelSig_1_StartConvert();		// start the ADC_DelSig_1 conversion
    
    // Initialize sleep timer

    // Interrupts
    CyGlobalIntEnable;
    rx_int_StartEx(RX_INT); 
    timer_int_StartEx(TIMER_INT);
    //tx_int_StartEx(TX_INT);
    //Sw_Mode_Int_StartEx(SW_INT);

    // Initialize UART
    UART_1_Start();                       
    UART_1_ClearRxBuffer();
    UART_1_ClearTxBuffer();
    LED_Write(0);
    LED_Mode_Write(0);
    
    // PWM module
    PWM_1_WritePeriod(255);
    
    // Initialize variables 
    double threshold = 0;
    userMode = 0;
    ledState = 0;
    currentPWM = 250;
    currentPhoto = 3700;
    
    // Send initial PWM 
    sendPWM(currentPWM);
    printPWM();

    for(;;)
    {
        
        //LCD_Char_1_Position(0, 11);
        //LCD_Char_1_PrintNumber(userMode);
        //printPhotoresistor();
        
        // Manual Mode
		/*if (userMode == MANUAL_MODE)
        {
            currentPWM = readPot();
            printPWM(currentPWM);
            sendPWM(currentPWM);
        }*/
        
        // Current average photoresistor values
        currentPhoto = getAvgPhotoresistors(); 
        
        // Time averaged photoresistor value 
        pushPhotoBuffer(currentPhoto);
        timeAvgPhoto = averagePhotoBuffer();
        printPhotoresistor(currentPhoto, timeAvgPhoto);
        
        // Automated Mode 
        if (userMode == AUTO_MODE || userMode == TIMED_MODE)
        {            
            // Adjust PWM if reading exceeds threshold
            int currentPhotoDiff = getPhotoDiff(timeAvgPhoto, initPhoto);
            if (abs(currentPhotoDiff) >= threshold)
            {
                LED_Write(!LED_Read());
                currentPWM = calcNewPWM(initPWM, currentPhotoDiff);
                
                // set LED lighting if necessary 
                if (ledPWMState == LIGHTING_ON)
                {
                    PWM_1_WriteCompare(ledPWM);
                    PWM_1_Start();
                }
                
                else if (ledPWMState == LIGHTING_OFF)
                {
                    PWM_1_Stop();   
                }
            }

            /*int currentPhotoPWMDiff = getPhotoPWMDiff(timeAvgPhoto, currentPWM);
            if (abs(currentPhotoPWMDiff - photoPWMDiff) >= threshold)
            {
                LED_Write(!LED_Read());
                currentPWM = calcNewPWM(timeAvgPhoto, photoPWMDiff);
            }*/
            
            
            /*if (timeAvgPhoto - initPhoto >= threshold)
            {
                int photoDiff = timeAvgPhoto - initPhoto;
                photoDiff /= 50;
                if (currentPWM - photoDiff < 245) currentPWM = 245;
                else currentPWM -= photoDiff;
                initPhoto = timeAvgPhoto;
                initPWM = currentPWM;
            }
            else if (initPhoto - timeAvgPhoto >= threshold)
            {
                int photoDiff = initPhoto - timeAvgPhoto;
                photoDiff /= 50;
                if (currentPWM + photoDiff > 255) currentPWM = 255;
                else currentPWM += photoDiff;
                initPhoto = timeAvgPhoto;
                initPWM = currentPWM;
            }*/
            
            // Print and send PWM 
            printPWM();
            sendPWM(currentPWM);
        }
    }

}

/*****************/
/* Potentiometer */
/*****************/

int readPot() 
{
    uint16 adcResult;
    uint8 transmitData;
    unsigned char j = 100;				// milliseconds delay
    
    if( ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) )
		{
			adcResult = ADC_DelSig_1_GetResult16();		// read the adc and assign the value adcResult 
       		if (adcResult & 0x8000)
       		{
        		adcResult = 0;                          // ignore negative ADC results
       		}
       		else if (adcResult >= 1024)
       		{
        		adcResult = 1024;                       // ignore high ADC results
       		}
            
            // Convert potentiometer reading to PWM 
            transmitData = adcResult*10./1024.;
            transmitData = 245. + (10. - transmitData);
		}   
    return transmitData;
}

/*******/
/* PWM */
/*******/

void sendPWM(int currentPWM)
{
    // Transmit data 
    UART_1_WriteTxData(currentPWM);
    
    // Toggle LED for debugging 
    /*ledState = !ledState;
    LED_Write(ledState);*/
    unsigned char j = 100;	
	CyDelay(j);		
}

void printPWM()
{
	/*LCD_Char_1_Position(0, 6);
	LCD_Char_1_PrintString("     ");			// clean up the previous display
	LCD_Char_1_Position(0, 6);*/
    
    // Current PWM
    LCD_Char_1_Position(1, 5);
    LCD_Char_1_PrintNumber(currentPWM);
    
    // Initial reference PWM
    LCD_Char_1_Position(1, 10);
    LCD_Char_1_PrintNumber(initPWM);
}

/******************/
/* Photoresistors */
/******************/

void pushPhotoBuffer(int photoValue)
{
    int i;
    for (i=bufferLength-1; i>=1; i=i-1)
    {
        photoBuffer[i] = photoBuffer[i-1];
    }
    photoBuffer[0] = photoValue;
}

int averagePhotoBuffer()
{
    int total = 0;
    int i;
    for (i=0; i<bufferLength; i=i+1)
    {
        total += photoBuffer[i];
    }
    return total/bufferLength;
}

void printPhotoresistor(int currentPhoto, int timeAvgPhoto)
{
    // Current time averaged photoresistor value
    LCD_Char_1_Position(0, 7);
	LCD_Char_1_PrintString("     ");
    LCD_Char_1_Position(0, 7);
  	LCD_Char_1_PrintNumber(timeAvgPhoto);
    
    // Reference photoresistor value
    LCD_Char_1_Position(0, 12);
  	LCD_Char_1_PrintNumber(initPhoto);
}

int readPhotoresistor()
{
    uint16 adcResult;
    unsigned char j = 100;				// milliseconds delay
    if( ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) )
		{
			adcResult = ADC_DelSig_1_GetResult16();		// read the adc and assign the value adcResult 
       		if (adcResult & 0x8000)
       		{
        		adcResult = 0;                          // ignore negative ADC results
       		}
            if (adcResult < 1750)
            {
                adcResult = 1750;   
            }
            if (adcResult > 4250)
            {
                adcResult = 4250;   
            }
			CyDelay(j);									// delay in milliseconds
		}
    return adcResult;
}

int getAvgPhotoresistors()
{
    int numMux = 3;
    int totalReading = 0;
    int i;
    for (i=1; i<=numMux; i=i+1)
    {
        AMux_1_Select(i);
        CyDelay(100);
        totalReading += readPhotoresistor();
    }
    return totalReading/numMux;         // current average photoresistor   
}

int getPhotoDiff(int currentPhoto, int initPhoto)
{
    int scaledCurrentPhoto = (currentPhoto/250) - 7;
    //if (scaledCurrentPhoto < 0) scaledCurrentPhoto = 0;
    //else if (scaledCurrentPhoto > 10) scaledCurrentPhoto = 10;
    
    int scaledInitPhoto = (initPhoto/250) - 7;
    return scaledCurrentPhoto - scaledInitPhoto;
}

/*int getPhotoPWMDiff(int timeAvgPhoto, int currentPWM)
{
    int scaledPhoto = (timeAvgPhoto/250) - 7;
    if (scaledPhoto < 0) scaledPhoto = 0;
    else if (scaledPhoto > 10) scaledPhoto = 10;
    int scaledPWM = currentPWM - 245;
    return scaledPWM - scaledPhoto;
}*/

int calcNewPWM(initPWM, currentPhotoDiff)
{
    ledPWMState = LIGHTING_OFF;     // default led lighting to off
    
    int scaledInitPWM = initPWM - 245;
    int scaledNewPWM = scaledInitPWM - currentPhotoDiff;
    int newPWM = scaledNewPWM + 245;
    if (newPWM < 245) newPWM = 245;
    else if (newPWM > 255) 
    {
        // enable LED lighting
        ledPWM = (newPWM - 255)*50;
        if (ledPWM > 255) ledPWM = 255;
        ledPWMState = LIGHTING_ON;
        
        // upper bound motor PWM
        newPWM = 255;
    }
    return newPWM;
}

/*int calcNewPWM(int timeAvgPhoto, int photoPWMDiff)
{
    int scaledPhoto = (timeAvgPhoto/250) - 7;
    if (scaledPhoto < 0) scaledPhoto = 0;
    else if (scaledPhoto > 10) scaledPhoto = 10;
    int scaledPWM = scaledPhoto - photoPWMDiff;
    
    int newPWM = scaledPWM + 245;
    if (newPWM < 245) newPWM = 245;
    else if (newPWM > 255) newPWM = 255;
    return newPWM;
}
*/


/*int getCurrentPWM()
{
    receivedPWM = 0;
    UART_1_WriteTxData(GET_CURRENT_PWM);
    while (!receivedPWM)
    {
        ;
    }
    return currentPWM;
}

int readPhotoresistor()
{
    int i;
    int numMux = 4;
    int totalReading = 0;
    for (i=1; i<=numMux; i=i+1)
    {
        AMux_1_Select(i);
        if( ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) )
		{
            totalReading += ADC_DelSig_1_GetResult16();
        }
    }
    return totalReading/numMux;
}

int autoMode(int initLight, int initPWM)
{
    int i;
    int numMux = 4;
    int totalReading = 0;
    for (i=1; i<=numMux; i=i+1)
    {
        AMux_1_Select(i);
        if( ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) )
		{
            totalReading += ADC_DelSig_1_GetResult16();
        }
    }
}*/

/* [] END OF FILE */
