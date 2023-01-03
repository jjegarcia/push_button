/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/application/LIGHTBLUE_service.h"
#include "mcc_generated_files/rn487x/rn487x_interface.h"
#include "mcc_generated_files/rn487x/rn487x.h"
#include "mcc_generated_files/drivers/uart.h"
#include "mcc_generated_files/ext_int.h"
#include "mcc_generated_files/tmr0.h"

/** MACRO used to reference Periodic Timer overflow flag Set. 
 *  This is used by the application to have a semi-accurate 
 *  periodic task execution rate. 
 *  Strict adherence to time interval is not required.
 */
//#define TIMER_FLAG_SET()                (TMR0_HasOverflowOccured())
/** MACRO used to reset the Periodic Timer overflow flag.
 *  This is used by the application to reload the semi-accurate
 *  periodic task execution.
 *  The rate allows for a (100%) drift prior to error
 *  Is susceptible to effect by extended BLE communication. 
 */
//#define RESET_TIMER_INTERRUPT_FLAG      (PIR0bits.TMR0IF = 0)
/** MACRO used to configure the application used buffer sizes.
 *  This is used by the application for communication buffers.
 */
#define MAX_BUFFER_SIZE                 (80)

static char statusBuffer[MAX_BUFFER_SIZE]; /**< Status Buffer instance passed to RN487X drive used for Asynchronous Message Handling (see *asyncBuffer in rn487x.c) */
static char lightBlueSerial[MAX_BUFFER_SIZE]; /**< Message Buffer used for CDC Serial communication when connected. Terminated by \r, \n, MAX character Passes messages to BLE for transmisison. */
static uint8_t serialIndex; /**< Local index value for serial communication buffer. */
static bool LED_ON;

void setListen(void);
void setPushed(void);
void setTimeout(void);
void setComplete(void);
void setAlert(void);
void blink(void);
void runProtocol(void);

#define IS_LED_ON()     (LED_ON==true)
#define SET_LED_ON()    (LED_ON=true)
#define CLEAR_LED_ON()  (LED_ON=false)

typedef enum {
    LISTEN,
    PUSHED,
    TIMEOUT,
    COMPLETE,
    ALERT
} _states;


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

