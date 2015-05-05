/************************ PIC18F452 displaying ADC values to 16x2 lcd ************************/
int i;
unsigned char ch;
unsigned int adc_rd;
char *text;
long tlong;

  void main()
    {
      ANSEL = 0;                  		// All I/O pins are configured as digital
      ANSELH = 0;
      CM1CON0.F7=0;                 		//Turn off comparator one and comparator two
      CM2CON0.F7=0;
      TRISB=0;
      Lcd_Config(&PORTB,4,5,6,3,2,1,0);   // Initialize LCD
      Lcd_Cmd(LCD_CURSOR_OFF);  	// Cursor off
      Lcd_Cmd(LCD_CLEAR);      	// Clear display
      text = "PROJECT ADC";               // assign text to string
      LCD_Out(1,1,text);                       // print string a on LCD, 1st row, 1st column
      text  = "voltage:";                      // assign text to string
      LCD_Out(2,1,text);                       // print string a on LCD, 2nd row, 1st column
        TRISA = 0;                  		       // Port A pins are configured as outputs
        TRISB = 0;	       		                 // Port B pins are configured as outputs
        TRISD = 0;                  		       // Port D pins are configured as outputs
        TRISC = 0;                  		       // Port C pins are configured as outputs
        Delay_ms(2000);                        // Wait for 2 sec for initilize of ADC to read value
        while(1)
    {

       ADCON1=0b10000000;       //adc initilize,  right justified, reference: Vdd, Vss
       ANSEL=0x0D;        //set AN2 (RAx) and AN3 (RAx) to analog
       TRISC=0x00;        //set C to outputs
       TRISB=0x00;        //set B to outputs
       TRISA=0b11000011;        //set AN2 (RAx) and AN3 (RAx) to inputs
       ADCON0=0x43;       //begin AD conversion on AN2
       while(ADCON0<2>=1)//wait until ADCON0<1> flips to 0
        continue;
       adc_rd = (ADRESL<<6);
       PORTD = adc_rd;      //write ADC result to portD
       tlong = (long)adc_rd * 3400;           // covert adc reading to milivolts
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

        }

}
