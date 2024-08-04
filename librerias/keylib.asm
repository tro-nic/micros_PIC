;* Estas subrutinas realizan la inicialización y detección de un teclado
;* tipo telefónico controlando las columnas con las salidas RB1,RB2 y RB3
;* y los renglones con las entradas RB4,RB5,RB6 y RB7
;* con resistencias pull-up internas para evitar resistencias externas.
;*********************************************************************;
;                  inicialización del puerto C:                      *;
;*********************************************************************;
	         org	0x440

initB    	CLRF      STATUS	 	;Selecciona Banco 0
	        CLRF      PORTC		;Inicializa latches de datos de PORTB
	        BSF       STATUS,RP0 		;Selecciona Banco 1
	        MOVLW     0xF0  		;configura RB7,...,RB4 como entradas
	        MOVWF     TRISC 		;y RB3,RB2,RB1 como salidas
	        BCF       OPCION,7  	;Conecta todas las resistencias Pull-Up
	        BCF       STATUS,RP0 		;regresa al Banco 0
	        RETURN

;Subrutina de Detección de tecla presionada: regresa w=0 si no hay tecla
;presionada y w=0xFF si hay alguna tecla presionada

CONFIGURA       BCF       PORTC,0
                BCF       PORTC,1 	;activa las cuatro columnas
        	BCF       PORTC,2
        	BCF       PORTC,3
	        
DETEC           BTFSS     PORTC,7 	;lee renglón 1,2,3
	        GOTO      rebo	        ;si tecla presionada limpia rebote
	        BTFSS     PORTC,6 	;lee renglón 4,5,6
	        GOTO      rebo  	;si tecla presionada limpia rebote
	        BTFSS     PORTC,5	 ;lee renglón 7,8,9
	        GOTO      rebo  	;si tecla presionada limpia rebote
	        BTFSS     PORTC,4 	;lee renglón *,0,#
	        GOTO      rebo   	;si tecla presionada limpia rebote
	        RETLW     0x0   	;no hbo tecla presionada retorna con w=0

rebo     	CALL      TEMPO1	;pausa de 50 milisegundos
	        
;**********************************;
;*          LEE FILAS             *;
;**********************************;

                BTFSS     PORTC,7	;lee renglón 1,2,3
	        RETLW     0xFF   	;tecla presionada, retorna con w=0xFF
	        BTFSS     PORTC,6 	;lee renglón 4,5,6
	        RETLW     0xFF          ;tecla presionada, retorna con w=0xFF
	        BTFSS     PORTC,5 	;lee renglón 7,8,9
	        RETLW     0xFF  	;tecla presionada, retorna con w=0xFF
	        BTFSS     PORTC,4 	;lee renglón *,0,#
	        RETLW     0xFF  	;tecla presionada, retorna con w=0xFF
	        RETLW     0x00  	;falsa alarma retorna con w=0

;*********************************;
;*    LEE COLUMNAS               *;
;*********************************;

cod1     	MOVLW    0xF7   	;desactiva todas las columnas
        	MOVWF    PORTC  	;y activa la columna 1,4,7,*
        	BTFSS    PORTC,7 	;Es la tecla 1?
        	RETLW    '1'    	;retorna código del '1'
        	BTFSS    PORTC,6	 ;Es la tecla 4?
        	RETLW    '4'     	 ;retorna código del '4'
	        BTFSS    PORTC,5	 ;Es la tecla 7?
	        RETLW    '7'	        ;retorna código del '7'
        	BTFSS    PORTC,4 	;Es la tecla *?
        	RETLW    '*'    	;Retorna código del '*'
        	MOVLW    0xFB   	;desactiva todas las columnas
          	MOVWF    PORTC  	;y activa la columna 2,5,8,0
        	BTFSS    PORTC,7 	;Es la tecla 2?
        	RETLW    '2'    	;retorna código del '2'
        	BTFSS    PORTC,6 	;Es la tecla 5?
        	RETLW    '5'    	;retorna código del '5'
        	BTFSS    PORTC,5 	;Es la tecla 8?
        	RETLW    '8'    	;retorna código del '8'
        	BTFSS    PORTC,4 	;Es la tecla 0?
        	RETLW    '0'    	;Retorna código del '0'
        	MOVLW    0xFD   	;desactiva todas las columnas
        	MOVWF    PORTC  	;y activa la columna 3,6,9,#
        	BTFSS    PORTC,7 	;Es la tecla 3?
        	RETLW    '3'    	;retorna código del '3'
        	BTFSS    PORTC,6 	;Es la tecla 6?
        	RETLW    '6'    	;retorna código del '6'
        	BTFSS    PORTC,5 	;Es la tecla 9?
                RETLW    '9'    	;retorna código del '9'
        	BTFSS    PORTC,4	 ;Es la tecla #?
        	RETLW    '#'    	;Retorna código del '#'
        	
                RETLW    0x00   	;falsa alarma, no hay tecla presionada



