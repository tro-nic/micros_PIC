
				list			p=12f508
				Radix			HEX

STATUS			EQU			0x03
OSCCAL			EQU			0x05	
GPIO			EQU			0x06				
conteo			EQU			0x07
coxa			EQU			0x08				
				
				
				__CONFIG	0xFEA
				
				org			0x00
				movwf		OSCCAL
				movlw		b'101000'
				TRIS		GPIO
				clrf		conteo				;Esta es la tarea
				
cosa			bcf			GPIO,0

otro			btfss		GPIO,5
				goto		otro

				movlw		0x0f
				xorwf		conteo,w
				btfss		STATUS,2
				goto		incrementa
				
				bsf			GPIO,0
				goto		otro


incrementa		incf		conteo,f
				goto		otro
				
				end
