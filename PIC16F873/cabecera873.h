

/* 
 * File:  cabecera 
 * Author: Angel Bautista
 * Comments: Intento de libreria generica
 * Revision history: 15/7/24
 * rev 1 28/07/24 
 * - se reorganiza la cebecera y se crean las librerias de cmomunicación
 */



#ifndef cabecera_873_H
#define	cabecera_873_H

#include <xc.h>
#include <stdio.h>
#include <pic16f873.h>
#include "imagen.c"

#define      _XTAL_FREQ     4000000

#include "uart.h"
#include "i2c.h"

#pragma config   FOSC = XT, DEBUG = OFF,  WDTE = OFF, CP = OFF, CPD = OFF, LVP = OFF, PWRTE = ON

/*                  Macros                        */

#define puertoA_on  PORTA = 0xFF
#define puertoA_off PORTA = 0x00
#define puertoB_on  PORTB = 0xFF
#define puertoB_off PORTB = 0x00
#define puertoC_on  PORTC = 0xFF
#define puertoC_off PORTC = 0x00
#define temporizador_on T1CONbits.T1CKPS = 1
#define temporizador_off T1CONbits.T1CKPS = 0

#define led_on PORTAbits.RA0 = 1
#define led_off PORTAbits.RA0 = 0

#define oled 0x3C
   
/* Variables*/

unsigned char comando[6];
unsigned int buffer_letra;
uint8_t memoria;
uint8_t men_bus;
uint16_t cont_led = 0;
__bit estado_led  = 0;

// Matematicas

uint16_t radio = 0;
uint16_t diametro = 0;


/*             Constantes                  */

const double pi = 3.1415926;

/***************************************************************/

__bit setup(void){
     if(iniciar_puertoSerial(9600)) led_on;
     iniciar_i2c();
    //Limpiar puertos asntes de configuracion
    puertoA_off;
    puertoB_off;
    puertoC_off;
    
    //configuracion de opciones globales
    OPTION_REG = 0b00000000;
    //Cofiguracion de puertos
    TRISA = 0X00; //salidas
    TRISB = 0X00; //salidas
    TRISC = 0b10011000; //salidas y RC3 y RC4 -> I2C / RC7 RX y RC6 TX
    INTCONbits.GIE = 0;
    
    //interrupcion de perifericos
    PIE1 = 0b00000000;
    /**********************/
    //BAnderas de interrupciones de PIE1
    PIR1 = 0b00000000;
    /*********************/
    //Interrupciones adicionales 8,7 y 5 -> OSC, Comparador, EEPROM  
    PIE2 = 0b00000000;
    // Bandera de interrupciones de PIE2
    PIR2 = 0b00000000;
   
    
    //Temporizador TMR1
    T1CON = 0b01001001;// Se activo el temporizador
    //T1CONbits.T1CKPS = 0b00; Preescalar 1:1
             
            
    puertoA_off;
    puertoB_off;
    puertoC_off;
    escribir_puertoSerial("Sistema iniciado\n");
    led_on;
    comando[5] = 0x00; //Ultimo caracter siempre va a ser null
    
    return 0; // Todo esta bien.
        }


#endif	

