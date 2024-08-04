/*
 * File:   principal.c
 * Author: angel
 *
 * Created on 9 de julio de 2024, 10:34 PM
 */

#include "cabecera873.h"

void inicia_pantalla(){
    //Pantalla direccion 0x78 -> 0x3C 
    inicio_transmision_i2c(0x3C);
    
    escribir_i2c(0x00);
    
    escribir_i2c(0xAE); 
    
    escribir_i2c(0xA8);
    escribir_i2c(0x3F);
    
    escribir_i2c(0xD3);
    escribir_i2c(0x00);
    
    escribir_i2c(0x40);
    
    escribir_i2c(0xA1);
    
    escribir_i2c(0xC8);
    
    escribir_i2c(0xDA);
    escribir_i2c(0x12);
   
    escribir_i2c(0x81);
    escribir_i2c(0x7F);
   
    escribir_i2c(0xA4);
   
    escribir_i2c(0xA6);
    
    escribir_i2c(0xD5);
    escribir_i2c(0x80);
   
    escribir_i2c(0x8D);
    escribir_i2c(0x14);
    
    escribir_i2c(0xAF);
    
    escribir_i2c(0x21);
    escribir_i2c(0x00);
    escribir_i2c(0x7F);
    escribir_i2c(0x22);        
    escribir_i2c(0x00);
    escribir_i2c(0x07);
   
    escribir_i2c(0x20);
    escribir_i2c(0x00);
    
    fin_transmision_i2c();
}

void main(void) {
setup();

//Pantalla OLED SSD1306
//fila 128 x 8 cada byte enviado son pixel en vertical
//Total 8 filas
// Inicia con 2 filas en amarillo
// 6 filas azules
// se carga de derecha a Izquierda

inicia_pantalla();
for(int i = 0; i < 1024; i++){
inicio_transmision_i2c(0x3C);
escribir_i2c(0x40);
escribir_i2c(0x80);
fin_transmision_i2c();
}

__delay_ms(500);

for(int i = 0; i < 1024; i++){
inicio_transmision_i2c(0x3C);
escribir_i2c(0x40);
escribir_i2c(0x00);
fin_transmision_i2c();
}

for(int i = 0; i < 1024; i++){
inicio_transmision_i2c(oled);
escribir_i2c(0x40);  // Indicar que se va a escribir la pantalla.
escribir_i2c(imagen[i]); // se escribe el dato
fin_transmision_i2c();
}

//circulo
radio = 40;

//area circulo PI*r^2;

uint16_t area = pi * radio * radio;

//for(int i = 0; i < 1024; i++){
//inicio_transmision_i2c(oled);
//fin_transmision_i2c();
//escribir_i2c(0x40);  // Indicar que se va a escribir la pantalla.
//
//escribir_i2c();
//}
while(1){
 
    //dibujar pantalla
        
        


//        if(PIR1bits.RCIF){
//            for (uint8_t i = 0;i<=4; i++){
//                 comando[i] = leer_puertoSerial();
//                 //numeros dec 48 - 57
//                // a - z 97  - 122
//
//                 if (comando[i]==0x0D) break; // Lee hasta que llega enter
//
//                if (comando[i] < 48 || comando[i] > 57)  {
//                    if(comando[i] < 97 || comando[i]>122){
//                        comando[i] = 0x00;
//                    }
//                }
//            }
//        
//            if(comando[0] == 0x00){
//                escribir_puertoSerial("Error");
//            }
//            else{
//            escribir_puertoSerial(comando);
//            }
//            escribir_puertoSerial(" -> comando\n");
//        }
//       
//   if(comando[0] == 'a'){
//       escribir_puertoSerial("Ejemplo: \n e502a -> e = escrbir\n direccion_bus = 50 Hex mem eeprom \n posicion memoria = 2\n dato a guardar = a\n");
//   }
//      
//     
//   if(comando[0] == 'e'){
//        
//    escribir_i2c(0x50,comando[1],comando[2]); // direccion memoria 24cxx -> 0101(A2)(A1)(A0) --> 1010000X = 0x050
//    escribir_puertoSerial("Dato escrito");
//   }
//         
//    if(comando[0] == 'l'){     
//         buffer_letra = leer_i2c(0x50,comando[1]);
//         escribir_puertoSerial("Dato leido: ");
//         enviar_caracter(buffer_letra);
//         enviar_caracter('\n');
//    }
//   
/*                 Control de led de vida               */   
    if(cont_led == 5000){
        
         if(estado_led){
            led_off;
            estado_led = 0;
        }
        else{
            led_on;
            estado_led = 1;
        }
        cont_led = 0;
    }

    cont_led++;
    
    //comando[0] ='0';
}
}


