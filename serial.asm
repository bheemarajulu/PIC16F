/******** UART 8 bits of data and baud rate of 19200. The project will simply receive a character from the hyper-terminal **/
/******** and send it back to hyper-terminal to display it again ***************/
void main() {

asm{

BCF STATUS,RP1  // Move to Bank 1

BSF STATUS,RP0 //As TXSTA,TRISC & SPBRG are in Bank 1

MOVLW 0X24 //Load W with 24H

MOVWF TXSTA  //For Asynchronous 8 bit data frame and low baud rate and

MOVLW 25  //Load W with 25

MOVWF SPBRG //Loading Baud Rate of 19200

BCF TRISC,6 //Configuring RC6 as output pin

BSF TRISC,7 //Configuring RC7 as input pin

BCF STATUS,RP0 //Moving to Bank 0

MOVLW 0X90 //Load W with 90H

MOVWF RCSTA //Enable continous recieve and 8 bit recieve

RECIEVE:

 BTFSS PIR1,RCIF //Checking if Reciever USART Buffer is full

 GOTO RECIEVE

 MOVF RCREG,W  //If full copy RCREG to Working register

MOVWF TXREG //Load TXREG with contents of RCREG and transmit

TRANSMIT:

 BTFSS PIR1,TXIF //Checking if Transmitter Usart Buffer is empty

 GOTO TRANSMIT //If not go to TRANSMIT

 GOTO RECIEVE //If empty go back to RECIEVE

}

}

// transmit enable
