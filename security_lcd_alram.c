/*********************** Security Monitoring using PIC16F ***********************/
char *key = "Ready to Arm"; // To display the text Ready to Arm
char *key1 = "Zone1 Armed"; // To display the text Zone1 Armed
char *key2 ="Zone2 Armed"; // To display the text Zone2 Armed
char *key3 = "Zone3 Armed"; // To display the text Zone3 Armed
char *key12 = "Zones 1&2 Armed"; // To display the text Zones 1 and 2 Armed
char *key13 = "Zones 1&3 Armed"; // To display the text Zones 1 and 3 Armed
char *key23 = "Zones 2&3 Armed"; // To display the text Zones 2 and 3 Armed

unsigned short b=10;
unsigned short a=0;
unsigned short j=0;
unsigned short k=0;
unsigned short y=0;
unsigned short x=0;
unsigned short number1 = 0;
short *digit = "00";
void led();
void init();
void push();
  

void Display_1_init() // define display_init;
 {
 digit[2] = (number1/10)%10 + 48; // // tens digit;
 digit[3] = (number1%10 +48); // unit digit;
 Lcd_Out(2,13,digit); // display on LCD from column 1, character 7;
 }


void breach() // Subroutine occurs when we have a security breach
{

 lcd_cmd(lcd_clear); // To clear the LCD screen
 Lcd_out_cp("security breach"); // To display the text security breach
 delay_ms(100);
 PORTD.F4=1; // To enable the fourth LED of PORTD
 if (PORTC.F5==1) // If the fifth push button of PORTC is pressed, it will reset.
 init();
}


void display() // Subroutine used to display different cases on the LCD.
{
lcd_cmd(lcd_clear) ; // Command to clear the LCD
if (PORTD!=0) // If PORTD is not zero, switch case will be executed.
{
switch(PORTD)
{
case 1: {
Lcd_out_cp(key1); // To display the text Zone1 Armed at the cursor position when ‘001’ is
// pressed
 }
break;
case 2: { Lcd_out_cp(key2); // To display the text Zone2 Armed at the cursor position when ‘010’ is
//pressed
}
break;
case 4: {
Lcd_out_cp(key3); // To display the text Zone3 Armed at the cursor position when ‘100’ is
//pressed
}
break;
case 3: {
Lcd_out_cp(key12); // To display the text Zones 1 and 2 Armed at the cursor position when
//‘011’ is pressed
}
break;
case 5: {
Lcd_out_cp(key13); // To display the text Zones 1 and 3 Armed at the cursor position when
//‘101’ is pressed
}
break;
case 6: {
Lcd_out_cp(key23); // To display the text Zones 2 and 3 Armed at the cursor position when
//‘101’ is pressed
}
break;
case 7: {
Lcd_cmd(lcd_clear); // Command to clear the LCD display
Lcd_out_cp(key);// To display the text Ready to Arm at the cursor position when ‘111’ is pressed
}
break;
case 8: // when system armed being all zones disarmed
case 9: // when system armed and zones 1,2 disarmed
case 10:
 case 11:
         {
          Lcd_out_cp("breach in");
          Lcd_out_cp("10 sec");
         for(j=0; j<9; j++)
           {
            led();
            number1++;
            Display_1_init();
            delay_ms(1000);
            if (PORTC.F5==1) // RC5 of PORTC is used for reset of the system
            init();
           }
           if(number1>8)
           {
            if (PORTC.F5==1) // RC5 of PORTC is used for reset of the system
            init();
            b=0;
            number1=0;
            }

            }
break;
case 12:
case 13:
case 14:
case 15:
default:
 break;
}
}
else
{
Lcd_out_cp("No zone armed"); //To display this when no zones armed
}

delay_ms(100);

}

void push() // Function to have the first 10s countdown for system armed
{

 b++;
 while(b!=0) // Execute this loop when b is not equal to zero
 {
 led(); // Subroutine for push button and LED
 Lcd_cmd(lcd_clear); // To clear the LCD display
 Lcd_out_cp("System Armed in"); // To display the desired text
 Lcd_out(2,1,"10");//To display "10" when b=10
 Lcd_out_cp(" sec"); // To display the text sec
 for(j=0; j<9; j++)
 {
  if (PORTC.F5==1) // To have the system to reset.
  init();
  number1++;
  led();
  Display_1_init();
  delay_ms(1000);
  led();
 }
 if(number1>8)
 {
  b=0;
  number1=0;
  }

 delay_ms(20); // To have a delay of 20 seconds
 if (PORTC.F5==1) // Fifth push button of PORTC is used as reset button
 init();
 }

 PORTD.F3=1; //To light an led of PORTD to indicate state

while(PORTD==15) // Execute this instruction when system armed and all zones armed
{
 led(); // To have the push button and LED
 Lcd_cmd(lcd_clear); // Command to clear the LCD display
 Lcd_out_cp("system armed") ;// To display the corresponding text
 if (PORTC.F5==1) // To have the system to reset.
 init();
 delay_ms(100); // To have a delay of 100 ms.

}

}



void init() // This function is to initialize all the parts we need
 //like turn off the A/D CONVERTER and two comparators
 //In addition, I initialize the ports and LCD in this part
{
ANSEL=0; //Don't use the port as analog inputs. See next line
ANSELH=0; // Configure all the ports as I/O bits. (Digital I/O)
CM1CON0=0; //To turn off comparator one and comparator two
CM2CON0=0;
TRISB=0; //To set PORTB as output because its related to LCD display
TRISC=255; // PORTC is set as input
PORTC=0; // To initialize the value of PORTC and set the port c as input, because
// we need to use RC3,RC4,RC5
TRISD=0; // To set PORTD as output.
PORTD=0; // To initialize the value of PORTD as zero.

b=0; // To initilize b
Lcd_Config(&PORTB,4,5,6,3,2,1,0); //To initialize lcd
Lcd_Cmd(LCD_CURSOR_OFF); // Command to off the Cursor on the LCD display
 }

void led()
{
if (PORTC.F0==1) //When push button RC0 is pressed, light RD0 or turn off RD0
{
 while(PORTC.F0);
PORTD.F0=!PORTD.F0;
}
 if (PORTC.F1==1) // When push button RC1 is pressed, light the RD1 or turn off RD1
 {
 while(PORTC.F1);
 PORTD.F1=!PORTD.F1;
}  if (PORTC.F2=1) // When push button RC2 is pressed, light the RD2 or turn off RD2
 {
 while(PORTC.F2) ;
PORTD.F2=!PORTD.F2;
}
if (PORTC.F4=1) // When push button RC1 is pressed,light the RD4 or turn off RD4
{
 while(PORTC.F4) ;
PORTD.F3=!PORTD.F3;
}

}

// Main Program //
void main()
{

init(); // To initialize all component
while(1)
{
if(PORTC.F5==1) // To have the system to reset.
init();
led();
if (PORTC.F3*PORTD.F0*PORTD.F1*PORTD.F2==1)
push();
else if ((b==0)*PORTD.F3==1) // Wait for 10 seconds
{
breach(); // Display the text security breach
number1++;  // Count of 10 sec
}
else display();
if (PORTC.F5==1) // RC5 of PORTC is used for reset of the system
init();
 }
 }

