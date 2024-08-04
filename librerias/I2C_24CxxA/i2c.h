#ifndef i2c_H
#define	i2c_H
#include <uart.h>

__bit iniciar_i2c(){
    // SSPCONbits.WCOL // Bandera de colicion poner a 0
    //SSPCONbits.SSPOV //Bandera 0 = overflow
   
   SSPCONbits.SSPM = 0x08; // I2C Master
   SSPCONbits.SSPEN = 1; // Activa el puerto en los pines 
   SSPSTATbits.SMP = 1;
  // SSPCON2 = 0b00000000;
    //Se define el reloj
    //clock = _XTAL_FREQ / (4 * (SSPADD+1)) --> 100Khz
    SSPADD = (_XTAL_FREQ / (4 * 100000)) - 1;
    
    return 0;
}

void espera_i2c(void){
    // Espera activacion
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
}

unsigned int leer_i2c(uint8_t dir_bus, unsigned int dir_memoria){
  /***************************************************************************/ 
  /********          Modulo interno I2C como transmisor  ********************/  
  dir_bus = (uint8_t)((dir_bus << 1) & 0b11111110);
  
   SSPCON2bits.SEN = 1;
  //SSPCON2bits.RSEN = 1;
    
    __delay_us(10);
    
    SSPBUF =  dir_bus ; // Informar que se va a leer un equipo en la direccion dir_bus
   while(SSPSTATbits.BF);
   
   while(SSPCON2bits.ACKSTAT){
        if(PIR1bits.SSPIF) {
        escribir_puertoSerial("Error direccionamiento bus / Ciclo lectura\n");
         SSPCON2bits.PEN = 1;
        return 1;
        }
   }
    espera_i2c();
    // __delay_us(10);
     SSPBUF = dir_memoria;
     while(SSPSTATbits.BF);
     
    while(SSPCON2bits.ACKSTAT){
        if(PIR1bits.SSPIF) {
        escribir_puertoSerial("Error direccionamiento memoria / Ciclo lectura\n");
        SSPCON2bits.PEN = 1;
        return 1;
        }
     }
  
   //__delay_us(10);
   
   SSPCON2bits.RSEN = 1;
     
     espera_i2c();
     
      SSPBUF = (uint8_t)(dir_bus + 1); // Iinformar que se va a leer
    while(SSPSTATbits.BF); // espera ecritura de buffer
 
    while(SSPCON2bits.ACKSTAT){
        if(PIR1bits.SSPIF) {
        escribir_puertoSerial("Error configuracion de lectura / Ciclo lectura\n");
        SSPCON2bits.PEN = 1;
        return 1;
        }
     }
    
    espera_i2c();
    
      /***************************************************************/
   /*          MOdulo en modo recepcion */
    
    
    SSPCON2bits.RCEN = 1; 
    
   while(!SSPSTATbits.BF);
  
    //espera_i2c();
    //__delay_us(10);
    
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN =1;// Ciclo de reconocer el envio
    
     __delay_us(10);
    
    SSPCON2bits.PEN = 1; // se cierra el envio
    espera_i2c();
    
    return SSPBUF;
}

void fin_transmision_i2c(){
    SSPCON2bits.PEN = 1; // se cierra el envio
    espera_i2c();
}

__bit inicio_transmision_i2c(uint8_t dir_bus){
    
       dir_bus = (uint8_t)((dir_bus << 1) & 0b11111110);
  
    SSPCON2bits.SEN = 1;
    
    __delay_us(10);
    
    SSPBUF =  dir_bus ; // Informar que se va a leer un equipo en la direccion dir_bus
    while(SSPSTATbits.BF);
    
    while(SSPCON2bits.ACKSTAT){
        if(PIR1bits.SSPIF) {
        escribir_puertoSerial("Error direccionamiento bus/ Ciclo escritura\n");
        SSPCON2bits.PEN = 1;
        PIR1bits.SSPIF = 0;
        return 1;
        }
    }
    
    // __delay_us(8);
     return 0;
}

__bit escribir_i2c(uint8_t dato){
    
   
     SSPBUF = dato; //Guardar Dato
    while(SSPSTATbits.BF); 
    
    while(SSPCON2bits.ACKSTAT){
        if(PIR1bits.SSPIF) {
        escribir_puertoSerial("Error dato/ Ciclo escritura\n");
        SSPCON2bits.PEN = 1;
        PIR1bits.SSPIF = 0;
        return 1;
        }
    }
    
//    SSPCON2bits.ACKDT = 1;
//    SSPCON2bits.ACKEN =1;// Ciclo de reconocer el envio
    return 0;
}



#endif
