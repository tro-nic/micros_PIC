/* 
 * File:   uart.h 
 * Author: Angel Bautista
 * Comments: Libreria para comunicación via uart "RS232"
 *  Revision history: 0 28/07/24 
 * -inicio de proyecto
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef uart_H
#define	uart_H

            
 __bit iniciar_puertoSerial(const long velocidad){
     
        uint8_t baudios = (uint8_t)((_XTAL_FREQ / (16*velocidad))- 1);
        //baudios = Fosc/16(SPBRG + 1) ; SPBRG-> 0 a 255
        if(baudios <= 0)baudios = 25; //9600 Baudios Alta velocidad asincrono 
        SPBRG = baudios;
        //configuración de transmision
        //TXSTAbits.CSRC = 0; // Slave mode reloj externo
         TXSTAbits.TXEN = 1;
      //  TXSTAbits.TX9 = 0; //8 bits
      //  TXSTAbits.SYNC = 0; // Asincrono
        TXSTAbits.BRGH = 1; // Alta velocidad
       // TXSTAbits.TX9 = 0; // bit de paridad.
        //Configuración de recepcion
        RCSTAbits.SPEN = 1; //Serial port activo, RB2 = RX / RB5 = TX
        RCSTAbits.CREN = 1; //recepción continua
      //  RCSTAbits.RX9 = 0; // 8 bits
        return 0;
    }
   
    void enviar_caracter(const char info){
        while(!TXSTAbits.TRMT);
        TXREG = info;
    }
       
    void escribir_puertoSerial(const char *info){
        uint8_t i = 0;

        while(info[i]!= '\0'){ // transmite hasta el caracter asignado 
                //Espera que se desocupe
                 enviar_caracter(info[i++]); //transmite y asigna el siguiente caracter
        }

    }
    
    unsigned char leer_puertoSerial(){

       // RCREG //Buffer
        while(!PIR1bits.RCIF); //Espera a que se termine de cargar el buffer

       //buffer
        if (RCSTAbits.OERR) { //Coreccion de error
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1; //recepción continua
        }

        return RCREG;
    }


#endif


