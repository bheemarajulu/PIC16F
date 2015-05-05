/*************************Executing Operations for ADD, SUB, MULT and DIV using serial input numbers*******/
void print(short a) ;
char*text[4];
char oper;
int a1,a2,a3;
unsigned long a;
unsigned long b;
unsigned char num1;
unsigned long num2;
unsigned long Calc;
signed short sum=0;
signed short dif=0;
signed short quo=0;
signed short rem=0;
signed short pro=0;
signed short n=0;
signed short number=0;
signed short j=0;
char  k;
unsigned char temp;
unsigned char  kbd[5],op[12];
unsigned char MyKey, i,u;
void USART_Write_Text(unsigned char *uart_text);
void USART_unget_char(unsigned short ch);
void USART_Read_Text(char *Output, unsigned int length);
int USART_get_char();
int get_2dig_num();
static char store_unget=0;   // store unget char.

//
// This function sends carriage-return and line-feed to USART
//
void Newline()
{
 USART_Write(0x0D); // Send carriage-return
 USART_Write(0x0A); // Send line-feed
}

//
// Start of MAIN program
//

void main()org 0x004
{

ANSEL=0;                       //Don't use the port as analog inputs. See next line
ANSELH=0;
CM1CON0.F7=0;                 //Turn off comparator one and comparator two because they are
CM2CON0.F7=0;
TRISB=0;
Lcd_Config(&PORTB,4,5,6,3,2,1,0);
Lcd_Cmd(LCD_CURSOR_OFF);
Lcd_Cmd(LCD_CLEAR);
Lcd_out(1,1,"LCD_Serial:");
USART_init(19200);                     // initialize USART module
USART_Write(10);
USART_Write(13);
USART_Write_Text("ENTER FIRST NUM");
USART_Write(10);
USART_Write(13);


while (! Usart_Data_Ready()) {;}
    {            // if data is received
        a= get_2dig_num();  // 1st digit
        Usart_Write(a); // Echo the character
        print(a) ;
     }
USART_Write(10);
USART_Write(13);
USART_Write_Text("ENTER SECOND NUM");


while (! Usart_Data_Ready()) {;}

    {            // if data is received
        b= get_2dig_num();  // 1st digit
        Usart_Write(b); // Echo the character
        print(b) ;
    }


while (! Usart_Data_Ready()) {;}
   {     // If data is received,
      oper = Usart_Read();
      print(c) ;
      }

 switch(oper)
       {
         case '+' :
Lcd_Cmd(LCD_CLEAR);
print(b) ;
lcd_out_cp(" ");
print(a);
quo=a+b;
lcd_out(2,1,"ADD=");
print(quo);
lcd_out_cp("  ");
rem=a-b;
lcd_out_cp("SUB=");
print(rem);
break;

case '*' :

Lcd_Cmd(LCD_CLEAR);
print(b) ;
lcd_out_cp(" ");
print(a) ;
quo=a*b;
lcd_out(2,1,"MUL=");
print(quo);
break;

case '/' :
Lcd_Cmd(LCD_CLEAR);
print(b) ;
lcd_out_cp(" ");
print(a) ;
quo=a/b;
lcd_out(2,1,"q=");
print(quo);
lcd_out_cp("  ");
rem=a % b;
lcd_out_cp("r=");
print(rem);
break;
}
}


void print(short x) {
number=x;
n=0;
if (x>=0){
while(number!=0)
{j=number%10;
number /= 10;
n++;
}

switch (n)
{
case 4: lcd_chr_cp(((x/1000) % 10)+48);
 case 3 :  lcd_chr_cp(((x/100) % 10)+48);
case 2:  lcd_chr_cp(((x/10) % 10)+48);
 case 1:  lcd_chr_cp((x % 10)+48);break;
  case 0:lcd_chr_cp(48);
 }

   }

   else{
   lcd_chr_cp(45);
   x=-x;
   while(number!=0)
{j=number%10;
number /= 10;
n++;
}

switch (n)
{
case 4: lcd_chr_cp(((x/1000) % 10)+48);
 case 3 :  lcd_chr_cp(((x/100) % 10)+48);
case 2:  lcd_chr_cp(((x/10) % 10)+48);
 case 1:  lcd_chr_cp((x % 10)+48);break;

 }

       }
       }

void USART_Write_Text(unsigned char *uart_text)
{
  unsigned char i;
  i=0;
  while(uart_text[i]!=0)
  {
   USART_Write(uart_text[i]);
   i++;
   }
  }

int USART_get_char() {
unsigned short ch;

   if (store_unget!=0) {
      ch = store_unget;
      store_unget = 0;
      return ch;
   }
   while (! Usart_Data_Ready()) {;} // wait for input

   return  Usart_Read();  // This is the only allowable instance of Usart_Read().
}

////////////////////////////////////////////////////////////////////////
void USART_unget_char(unsigned short ch) {
   store_unget = ch;
}


//
int get_2dig_num() {
unsigned short ch1,ch2, ch3;

   ch1= USART_get_char();  // 1st digit
   USART_Write(ch1);
   if (! isdigit(ch1) ) {   // Not a digit so fail and exit.
      USART_unget_char(ch1);
      return -1;
   }

   ch2 = USART_get_char();  // 2nd digit
   USART_Write(ch2);
   if (! isdigit(ch2) ) {    // Not a digit so fails.
      USART_unget_char(ch2);
      // use the single digit in this case
      return (ch1-'0');
   }
   
   ch3 = USART_get_char();  // 2nd digit
   USART_Write(ch3);
   if (! isdigit(ch3) ) {    // Not a digit so fails.
      USART_unget_char(ch3);
      // use the single digit in this case
      return (ch2-'0');
   }

   return ((ch1-'0')*100) + ((ch2-'0')*10) + (ch3-'0');
}
