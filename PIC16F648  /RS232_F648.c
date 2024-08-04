/*
 * Ejemplo descargado desde la web
 * 
 * File:   RS232.c
 * Author: angel
 *
 * Created on 18 de octubre de 2022, 06:45 PM
 */

#include <xc.h>

#define _XTAL_FREQ 4000000

#pragma config FOSC = INTOSCIO, WDTE = OFF, PWRTE = OFF, LVP = OFF, MCLRE = ON, BOREN = OFF

/*******************ojo*********************/
/*          CODIGO DESBLOQUEADO            */
#pragma config CP = OFF, CPD = OFF
/*******************************************/

/********************** UART functions **************************/
void UART_Init(const long baud_rate)
{
  unsigned int n = ( _XTAL_FREQ / (16 * baud_rate) ) - 1;
  
  if (n < 0)
    n = 0;
 
  if (n > 255)  // low speed
  {
    n = ( _XTAL_FREQ / (64 * baud_rate) ) - 1;
    if (n > 255)
      n = 255;
    SPBRG = n;
    TXSTA = 0x20;  // transmit enabled, low speed mode
  }
 
  else   // high speed
  {
    SPBRG = n;
    TXSTA = 0x24;  // transmit enabled, high speed mode
  }
 
  RCSTA = 0x90;  // serial port enabled, continues receive enabled
 
}
 
__bit UART_Data_Ready()
{
  return RCIF;  // return RCIF bit (register PIR1, bit 5)
}
 
unsigned char UART_GetC()
{
  while (RCIF == 0) ;  // wait for data receive
  if (OERR)  // if there is overrun error
  {  // clear overrun error bit
    CREN = 0;
    CREN = 1;
  }
  return RCREG;        // read from EUSART receive data register
}
 
void UART_PutC(const char data)
{
  while (TRMT == 0);  // wait for transmit shift register to be empty
  TXREG = data;       // update EUSART transmit data register
}
 
void UART_Print(const char *data)
{
  unsigned int i = 0;
  while (data[i] != '\0')
    UART_PutC (data[i++]);
}
/********************** end UART functions **************************/
 
const char message[] = "Ejemplo" ;
 
void setup(void){
    PCON = 0X08;
    VRCON = 0x00;
    CMCON = 0x07;
    INTCON = 0x00;  
    PIE1 = 0x00;
    PIR1 = 0x00;
    OPTION_REG = 0x17;
    TRISA =  0x00;
    TRISB = 0x02;     
      
}


// main function
void main(void)
{
  setup();
  
  UART_Init(9600);  // initialize UART module with 9600 baud
 
  __delay_ms(2000);  // wait 2 seconds
 
  UART_Print("\r\n Holis soy tronic\r\n");  // UART print
 
  __delay_ms(1000);  // wait 1 second
 
  UART_Print(message);  // UART print message
 
  __delay_ms(1000);  // wait 1 second
 
  UART_Print("\r\n");  // start new line
 
 
 
  while(1)
  {
    if ( UART_Data_Ready() )  // if a character available
    {
      unsigned int c = UART_GetC();  // read from UART and store in 'c'
      UART_PutC(c);  // send 'c' via UART (return the received character back)
    }
 
  }
 
}
