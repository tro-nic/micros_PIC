                     cblock            0x12a
                     LCD_TEMP_1
                     LCD_TEMP_2
                     endc
                

 org             0x40
#DEFINE OFF_COMANDO BCF RA,0 	;DESACTIVA RS (MODO COMANDO)
#DEFINE ON_COMANDO  BSF RA,0 	;ACTIVA RS (MODO DATOS)
#DEFINE ENABLE      BSF RA,2 	;ACTIVA E
#DEFINE DISABLE     BCF RA,2	        ;DESACTIVA

;SE CONFIGURA EL PIC PARA QUE TRABAJE CON EL LCD.
;----------------------------------------------------------------------------------

UP_LCD		        BSF     	STATUS,RP0 		;BANCO 1
		  	clrf            RA
                        CLRF    	PORTD
			BCF     	STATUS,RP0 		;BANCO 0
			OFF_COMANDO 			;RS=0
			DISABLE 			;E=0
			RETURN

;----------------------------------------------------------------------------------
		;SE IMPLEMENTA UN RETARDO ENTRE DATOS Y COMANDOS HACIA EL LCD
;----------------------------------------------------------------------------------
LCD_BUSY        	CALL    	LCD_DELAY_2		;LLAMA RETARDO
			RETURN

;----------------------------------------------------------------------------------
		;ACTIVA Y DESACTIVA EL LCD
;----------------------------------------------------------------------------------
LCD_E 			ENABLE				;ACTIVA E
			CALL   LCD_DELAY
			DISABLE				;DESACTIVA E
			RETURN

;----------------------------------------------------------------------------------
		;PASA EL CONTENIDO CARGADO EN EL REGISTRO W A LA CGRAM.
;----------------------------------------------------------------------------------
LCD_DATO 		OFF_COMANDO 			;DESACTIVA RS (MODO COMANDO)
			MOVWF   	PORTD 			;VALOR ASCII A SACAR POR PORTB
			CALL    	LCD_BUSY 		;ESPERA A QUE SE LIBERE EL LCD
			ON_COMANDO 			;ACTIVA RS (MODO DATO)
			CALL    	LCD_E 			;GENERA PULSO DE E
	 		RETURN

;----------------------------------------------------------------------------------
		;CODIGO DE UN COMANDO PARA EL LCD
;----------------------------------------------------------------------------------
LCD_REG 		OFF_COMANDO 			;DESACTIVA RS (MODO COMANDO)
			MOVWF   	PORTD 			;CODIGO DE COMANDO
			CALL    	LCD_BUSY 		;LCD LIBRE?.
			CALL    	LCD_E 			;SI, GENERA PULSO DE E.
	 		RETURN

;----------------------------------------------------------------------------------
		;SECUENCIA DE INICIALIZACION DEL MODULO LCD
;----------------------------------------------------------------------------------
LCD_INI			MOVLW   	B'00111000'
			CALL    	LCD_REG 		;CODIGO DE INSTRUCCION
			CALL    	LCD_DELAY		;TEMPORIZA
			MOVLW   	B'00111000'
			CALL    	LCD_REG			;CODIGO DE INSTRUCCION
			CALL    	LCD_DELAY		;TEMPORIZA
			MOVLW   	B'00111000'
			CALL    	LCD_REG			;CODIGO DE INSTRUCCION
			CALL    	LCD_DELAY		;TEMPORIZA
			RETURN

;----------------------------------------------------------------------------------
		;BORRA EL DISPLAY Y RETORNA EL CURSOR A LA POSICION 0.
;----------------------------------------------------------------------------------
BORRA_Y_HOME    	MOVLW   	B'00000001' 		;BORRA LCD Y HOME.
	        	CALL    	LCD_REG
        		RETURN

;----------------------------------------------------------------------------------
		;RUTINA DESPLAZAMIENTO DEL CURSOR
;----------------------------------------------------------------------------------
CURSOR		        MOVLW    	B'00000110' 		;DESPLAZA CURSOR
			CALL    	LCD_REG
			RETURN

;----------------------------------------------------------------------------------
		;CONTROL DEL DISPLAY Y CURSOR.
;----------------------------------------------------------------------------------
DIS_ON_CUR_OFF	       MOVLW            B'00001100'	 	;LCD ON, CURSOR OFF.
		       CALL     	LCD_REG
		       RETURN

;----------------------------------------------------------------------------------
		;CONTROL DEL DISPLAY Y CURSOR.
;----------------------------------------------------------------------------------
DIS_ON_CUR_ON	       MOVLW           B'00001111' 		;LCD ON, CURSOR OFF.
		       CALL 	       LCD_REG
		       RETURN

;----------------------------------------------------------------------------------
		;IMPLEMENTA UN RETARDO
;----------------------------------------------------------------------------------
LCD_DELAY		MOVLW   	.10
			MOVWF   	LCD_TEMP_1
			CLRF 	        LCD_TEMP_2
LCD_DELAY_1 	        DECFSZ  	LCD_TEMP_2,F
			GOTO    	LCD_DELAY_1
			DECFSZ  	LCD_TEMP_1,F
			GOTO    	LCD_DELAY_1
			RETURN

;----------------------------------------------------------------------------------
		;IMPLEMENTA UN RETARDO  ENTRE CARACTERES
;----------------------------------------------------------------------------------
LCD_DELAY_2		MOVLW   	.03
			MOVWF   	LCD_TEMP_1
			CLRF    	LCD_TEMP_2
LCD_DELAY_1_2   	DECFSZ  	LCD_TEMP_2,F
			GOTO    	LCD_DELAY_1_2
			DECFSZ  	LCD_TEMP_1,F
			GOTO    	LCD_DELAY_1_2
			RETURN


