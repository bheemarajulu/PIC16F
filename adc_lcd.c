/******************************** Displaying ADC result on LCD using PIC16F887 on mikroelektronika PIC16 board**********/
unsigned char ch;
unsigned int adc_rd;
char *text;
long tlong;

void main() {
  ADCON0 = 0b01001001;        //Fosc/8 speed, AN2, ADON
  //ADCON1 = 0b10000000;         // right justified, reference: Vdd, Vss
  INTCON = 0;                  // disable all interrupts
  ANSEL  = 0x04;               // Configure AN2 pin as analog input
  TRISA  = 0x04;
  ANSELH = 0;                  // Configure other AN pins as digital I/O
  Lcd_Config(&PORTB, 4, 5, 6, 3, 2, 1, 0); // Lcd_Init_EP5, see Autocomplete
  LCD_Cmd(LCD_CURSOR_OFF);                 // send command to LCD (cursor off)
  LCD_Cmd(LCD_CLEAR);                      // send command  to LCD (clear LCD)

  text = "PROJECT ADC";               // assign text to string
  LCD_Out(1,1,text);                       // print string a on LCD, 1st row, 1st column
  text = "LCD example";                    // assign text to string
  LCD_Out(2,1,text);                       // print string a on LCD, 2nd row, 1st column

  ADCON1     = 0x82;                       // configure VDD as Vref, and analog channels
  TRISA      = 0xFF;                       // designate PORTA as input
  Delay_ms(2000);
  text  = "voltage:";                      // assign text to string
  while (1) {
    while(ADCON0<2>=1)                     //wait until ADCON0<1> flips to 0
      continue;
    adc_rd  = ADRESH;                      // get ADC value from 2nd channel
    LCD_Out(2,1,text);                     // print string a on LCD, 2nd row, 1st column

    tlong = (long)adc_rd * 5000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV

    ch     = tlong / 1000;                 // extract volts digit
    LCD_Chr(2,9,48+ch);                    // write ASCII digit at 2nd row, 9th column
    LCD_Chr_CP('.');

    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point

    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point

    ch    = tlong % 10;                    // extract 0.001 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('V');

    Delay_ms(1);
  }
