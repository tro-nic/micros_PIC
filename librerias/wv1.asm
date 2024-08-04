;**********************************************************;
;     CONTROL DE POTENCIA POR MEDIO DE PWM                 ;
;**********************************************************;


	list		 p=16f84a


	status          equ   0x01
	porta           equ   0x02
	portb           equ   0x03
	taux		equ     0x20
	cont		equ	0x21
	cont1		equ	0x22
	cont2		equ	0x23
	cont3		equ	0x24
	cont4		equ	0x25

	RADIX		 HEX


	org 		0x00

        goto		inicio
	org		0x05

inicio
      bsf         status,5
      clrf        portb
      movlw       0xff
      movwf       porta
      bcf         status,5
      clrf	  taux
      clrf        porta
      clrf        portb
lectura


;AUMENTO DE ANCHURA;

MAS	btfsc		porta,0
	goto		planB
	movlw		0x19
	addwf		taux,1
	btfsc		status,2
	call		alarma
	call		PWM	

;DISMINUCION DE ANCHURA;

menos	btfsc 	porta,1
	goto		planB
	movlw		0x19
	subwf		taux,1
	btfsc		status,2
	call		alarma
	call		PWM
	goto		lectura



;MODULO DEL PWM;

PWM  	bsf		portb,0
        call		tiempo
	bcf		portb,0
	call		tiempo1
	return          



;sistema sin modificacion de frecuencia;

planB	call		PWM
	goto		lectura



;modulo de alarma;


alarma	bsf		portb,7
	call		tiempo2
	bcf		portb,7
	movlw		0x01
	addwf		cont,f
	movlw		0x04
	xorwf		cont,0
	btfsc		status,2
	goto		alarma
	return
	

;BLOQUES DE TIEMPOS;

tiempo
	clrf		cont1
	clrf		cont2
newt	movlw		0x01
	addwf		cont1,1
	movlw		taux
	xorwf		cont1
	btfss		status,2
	goto		newt
	movlw		0x01
	addwf		cont2,1
	movlw		0x0a
	xorwf		cont2
	btfss		status,2
	goto		newt
	return



tiempo1
	clrf		cont3
	clrf		cont4
newt1	movlw		0x01
	addwf		cont3,1
	movlw		0xfa
	xorwf		cont3
	btfss		status,2
	goto		newt1
	movlw		0x01
	addwf		cont4,1
	movlw		0x03
	xorwf		cont4
	btfss		status,2
	goto		newt1
	return


tiempo2
	call		tiempo1
	call		tiempo1
	return
	

	 end
