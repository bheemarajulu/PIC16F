/****************** Assembly code to compare two values for greater, lesser and equal values *******************/
void main()
{
 TRISA = 0x00;        	// Clear all registers to configure or define the bits of the
 TRISB = 0x00;      	//Corresponding data registers as outputs.
 TRISC = 0x00;
 TRISD = 0x00;
 //PORTC =50;
 //PORTD = 70;

asm {
BSF STATUS,RP1      //Move to BANK3 by setting RP0 and RP1 bits in status register
BSF STATUS,RP0
CLRF ANSEL   	// Don't use the port as analog inputs
CLRF ANSELH         	//Configure all the PORTS as I/O bits.
BCF S	TATUS,RP0  	//Move to BANK2 by clearing RP0 and setting RP1
BSF STATUS,RP1
CLRF CM1CON0     	// Turn off comparator one and comparator two because they are
CLRF CM2CON0     	//associated with PORTA & PORTB
BCF STATUS, RP1   	//Move to page 0 by clearing RP0 and RP1 bits in status register
BCF STATUS, RP0
CLRF PORTA
       	//Clear port A data register (assign 0's to all bits of port A)
CLRF PORTB        	//Clear port B data register (assign 0's to all bits of port B)
CLRF PORTC       	//Clear port C data register (assign 0's to all bits of port C)
CLRF PORTD      	//Clear port D data register (assign0's to all bits of portD)
CLRF PORTE      	//Clear port E data register (assign0's to all bits of port E)
BSF STATUS,RP0  	//Move to bank 1 by setting RP0 and clear RP1.
BCF STATUS,RP1
CLRF TRISA        	// Clear all registers to configure or define the bits of the
CLRF TRISB       	//Corresponding data registers as outputs.
CLRF TRISC
CLRF TRISD
CLRF TRISE

BCF STATUS,RP1    	//Move to bank 0 by clearing RP0 and RP1
BCF STATUS,RP0

MOVLW      255      // Input Value of PORTC
MOVWF      PORTC

MOVLW      255       // Input Value of PORTD
MOVWF      PORTD


movf PORTC,W
subwf PORTD,W
btfsc  STATUS,Z    // Test for Zero flag set
goto PickC
btfsc STATUS,C
goto PickB

PickA:                      // A>B
      //COMF PORTA         	//Complement of PORTA
      CLRF TRISC
      CLRF TRISD
      BSF PORTB,0
      goto End            // A>B

PickB:                      // B<A
       //COMF PORTB        	//Complement of PORTB
       CLRF TRISC
       CLRF TRISD
       BSF PORTB,1
       goto End

PickC:                       // A==B
       //COMF PORTE        	//Complement of PORTB
       CLRF TRISC
       CLRF TRISD
       BSF PORTB,2
       goto End

END:
     NOP
    }
 }
