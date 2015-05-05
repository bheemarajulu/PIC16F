/************************ TIMER Program that Displays Count Time on the LCD display *******************/

/**********************TIMERPROGRAM********************************************/
/*---------------------Bheema Rajulu-------------------------------------------------*/
/**********************Header******************************************************/
    char Message1[]="TIME IN SEC:";         // Message for line1;
    char Message2[]="T7:";         // Message for line1;
    char Message3[]="T4:";         // Message for line1;
    unsigned int number1 = 0;
    unsigned int number2 = 0;
    unsigned int number3 = 0;
    unsigned int number4 = 0;
    unsigned int number5 = 0;
    char *digit = "0000";
    char *count = "0000";
    char *mount = "0000";
    int i;

    void Display_init()   // define display_init;
    {
     digit[0] = number1/1000 + 48;           // thousands digit;
     digit[1] = (number1/100)%10 +48;        // hundreds digit;
     count[2] = (number2/10)%10 + 48;        // tens digit;
     count[3] = number2%10 +48;              // unit digit;
     Lcd_Out(1,13,count);                    // display on LCD from column 1, character 7;
    }

    void Display_1_init()   // define display_init;
    {
     digit[0] = number1/1000 + 48;           // thousands digit;
     digit[1] = (number1/100)%10 +48;        // hundreds digit;
     digit[2] = (number1/10)%10 + 48; //        // tens digit;
     digit[3] = number1%10 +48;              // unit digit;
     Lcd_Out(2,4,digit);                    // display on LCD from column 1, character 7;
    }

    void Display2init()   // define display_init;
    {
     mount[0] = number5/1000 + 48;           // thousands digit;
     mount[1] = (number5/100)%10 +48;        // hundreds digit;
     mount[2] = (number5/10)%10 + 48; //        // tens digit;
     mount[3] = number5%10 +48;              // unit digit;
     Lcd_Out(2,13,mount);                    // display on LCD from column 1, character 7;
    }

  void main()
    {

        ANSEL = 0;                  // All I/O pins are configured as digital
        ANSELH = 0;
        CM1CON0.F7=0;                 //Turn off comparator one and comparator two
        CM2CON0.F7=0;
        TRISB=0;
        Lcd_Config(&PORTB,4,5,6,3,2,1,0);   // Initialize LCD
        Lcd_Cmd(LCD_CURSOR_OFF);  // Cursor off
        Lcd_Cmd(LCD_CLEAR);      // Clear display
        Lcd_out(1,1,Message1);                 // display message1 from column 1;
        Lcd_out(2,1,Message2);                 // display message2 from ROW 2, character 1;
        Lcd_out(2,9,Message3);                 // display message3 from ROW 2, column 9;

        TRISA = 0;                  // Port B pins are configured as outputs
        TRISB = 0;
        TRISD = 0;                  // Port B pins are configured as outputs
        TRISC = 0;                  // Port B pins are configured as outputs

        do {

        PORTA = 0x00;               // PORTA as Input
        PORTA = 0x00;
        PORTC = 0x00;               // PORTC as Input
        PORTD = 0x00;               // PORTD as Input
        display_init();
        delay_ms(1000);             // Delay 1 Sec
        number2++;                  // Increment counter by +1
        number3++;                  // Increment counter by +1
        number4++;                  // Increment counter by +1
        display_1_init();
        number1 = number1 + 7;      // Increment counter by +7
        Display2init();
        number5 = number5 + 4;      // Increment counter by +4
        if (number1>99)       // if it's more than 99 go to 0;
                {
                number1=0;
                  }

                if (number5>99)   // if it's more than 99 go to 0;
                {
                number5=0;
                  }

        if( number3 == 4)    // Count Repeats every 4 time
        {
                for(i=0; i<3; i++)
               {
                display_init();
                number2++;               // Increment counter by +1
                display_1_init();
                number1 = number1 + 7;   // 2nd ROW Every 7th increment number
                Display2init();
                number5 = number5 + 4;   // 2nd ROW Every 4th increment number

                if(i>0)
                {
                  display_init();
                  //number2++;
                  PORTB = 0xFF;      // Change port A state to High

                }

                if (number1>99)   // if it's more than 99 go to 0;
                {
                number1=0;
                  }

                if (number5>99)  // if it's more than 99 go to 0;
                {
                number5=0;
                  }
                //number3++;
                PORTD = 0xFF;     // Change port D state to High
                delay_ms(1000);
               }
              // number4 = number4+3;

               PORTD = 0x00;     // Change port D state to LOW
               PORTB = 0x00;     // Change port A state to LOW
               number3=0;
               number4 = number4+3; // Make counter to adjust delay of 3 sec, to mach counts of 7 sec
          }

          if(number4 ==7)
          {
                for(i=0; i<5; i++)
               {
                Display_init();
                number2++;
                display_1_init();
                number1 = number1 + 7;  // 2nd ROW Every 7th increment number
                Display2init();
                number5 = number5 + 4;  // 2nd ROW Every 4th increment number
                
                 if (number1>99)   // if it's more than 99 go to 0;
                {
                number1=0;
                  }

                if (number5>99)   // if it's more than 99 go to 0;
                {
                number5=0;
                  }
                //number4++;
                PORTC = 0xFF;     // Change port C state to High
                delay_ms(1000);
               }
                PORTC = 0x00;     // Number in port C is inverted
                number4=0;
                number3=0;
            }

        if (number2 > 99u)                 // if it's more than 99 go to 0;
        {
          number2 = 0;
        }

        } while (1);
    }

