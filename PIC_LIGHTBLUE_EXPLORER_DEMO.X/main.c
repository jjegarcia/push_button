/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated for use with PIC-Explorer

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */
#include "main.h"

_states state = LISTEN;
int counter = 0;

/*
                     Main application
 */
int main(void) {
    int COUNTER_THRESHOLD = 99999999999;

    // initialize the device
    SYSTEM_Initialize();
    RN487X_SetAsyncMessageHandler(statusBuffer, sizeof (statusBuffer));

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    RN487X_Init();
    LIGHTBLUE_Initialize();

    while (1) {
        //        if (RN487X_IsConnected() == true) {
        switch (state) {
            case LISTEN:
                if (IS_BUTTON_ACTIVE()) {
                    BUTTON_ACTIVE_CLEAR();
                    if (!IS_BUTTON_INITIALISED()) {
                        BUTTON_INITIALISED();
                    } else {
                        setPushed();
                    }
                }
                break;
            case PUSHED:
                if (TIMER_FLAG_SET() && !IS_BUTTON_ACTIVE()) {
                    setTimeout();
                } else {
                    if (IS_BUTTON_ACTIVE()) {
                        setListen();
                    }
                }
                break;
            case TIMEOUT:
                if (TIMER_FLAG_SET()) {
                    blink();
                    if (IS_BUTTON_ACTIVE()) {
                        setComplete();
                    }
                }
                break;
            case COMPLETE:
                counter++;
                blink();
                if (counter == COUNTER_THRESHOLD && !IS_BUTTON_ACTIVE()) {
                    setReset();
                } else {
                    if (IS_BUTTON_ACTIVE()) {
                        setTimeout();
                    }
                }
                break;
            case RESET:
                setListen();
                break;
        }
        //        } else {
        //            while (RN487X_DataReady()) {
        //                uart[UART_CDC].Write(RN487X_Read());
        //            }
        //            while (uart[UART_CDC].DataReady()) {
        //                RN487X.Write(uart[UART_CDC].Read());
        //            }
        //        }
    }
    return 0;
}

void setListen(void) {
    DataLedOff();
    BUTTON_ACTIVE_CLEAR();
    SLOW_MODE();
    EXT_INT_fallingEdgeSet();
    state = LISTEN;
}

void setPushed(void) {
    DataLedOn();
    EXT_INT_risingEdgeSet();
    RELOAD_TIMER();
    RESET_TIMER_INTERRUPT_FLAG;
    START_TIMER();
    state = PUSHED;
}

void setTimeout(void) {
    FAST_MODE();
    RELOAD_TIMER();
    RESET_TIMER_INTERRUPT_FLAG;
    BUTTON_ACTIVE_CLEAR();
    EXT_INT_fallingEdgeSet();
    state = TIMEOUT;
}

void setComplete(void) {
    BUTTON_ACTIVE_CLEAR();
    EXT_INT_risingEdgeSet();
    counter = 0;
    state = COMPLETE;
}

void setReset(void) {
    BUTTON_ACTIVE_CLEAR();
    EXT_INT_fallingEdgeSet();
    state = RESET;
}

void blink(void) {
    RESET_TIMER_INTERRUPT_FLAG;
    if (IS_LED_ON()) {
        CLEAR_LED_ON();
        DataLedOff();
    } else {
        SET_LED_ON();
        DataLedOn();
    }

}
/**
 End of File
 */
