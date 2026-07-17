#include <LPC21XX.H>
#include <string.h>

#define led1 (1<<23)	   

#define led2 (1<<24)	  

#define mr1 (1<<25)

#define mr2 (1<<26)	   


#define LCD_D (0xff<<14) 
#define RS (1 << 12) 
#define E (1 << 13) 

void UART0_CONFIG(void);

void UART0_Tx(unsigned char);

unsigned char UART0_Rx(void);
void UART0_STR(unsigned char *s);

void delay_ms(unsigned int ms);
void GSM_INIT(void);
void GSM_SEND_SMS(void );


void LCD_INIT(void);
void LCD_COMMAND(unsigned char cmd);
void LCD_CHAR(unsigned char data);
void LCD_STR(unsigned char *s);



char buffer[100];

int main()
{
    unsigned char ch;
    unsigned int i;
      IODIR0 |=LCD_D|RS|E;

       IODIR1 |= led1|led2|mr1|mr2; 

    LCD_INIT();
    
    LCD_COMMAND(0x80); 
    LCD_STR(" GSM HOME AUTOMATION ");
    //LCD_CMD(0xC0); 
    //LCD_STRING(" INITIALIZING.. ");
    
    UART0_CONFIG();
    delay_ms(2000); 
    GSM_INIT();
	GSM_SEND_SMS();


    while(1)
    {
        do {
            ch = UART0_Rx();
        } while(ch != '+');
        
        i = 0;
        do {
            buffer[i++] = UART0_Rx();
        } while(buffer[i-1] != '#');
        
        buffer[i-1] = '\0'; // Null-terminate string
        
       UART0_STR((unsigned char*)(buffer));

        LCD_STR((unsigned char *)(buffer));


LCD_COMMAND(0xc0);

if(strstr(buffer,"FAN ON")!=NULL)

{

IOSET1=mr1;

IOCLR1=mr2;

LCD_COMMAND(0X01);

LCD_STR("FAN ON");

}


else if(strstr(buffer,"FAN OFF")!=NULL)

{

IOCLR1=mr1;

IOCLR1=mr2;

LCD_COMMAND(0X01);

LCD_STR("FAN OFF");

}


else if(strstr(buffer,"LIGHT1 ON")!=NULL)

{

IOCLR1=led1;


LCD_COMMAND(0X01);

LCD_STR("LIGHT1 ON");

}


else if(strstr(buffer,"LIGHT2 ON")!=NULL)

{ 


IOCLR1=led2;


LCD_COMMAND(0X01);

LCD_STR("LIGHT2 ON");

}


else if(strstr(buffer,"LIGHT1 OFF")!=NULL)

{

IOSET1=led1;

LCD_COMMAND(0X01);

LCD_STR("LIGHT1 OFF");

}


else if(strstr(buffer,"LIGHT2 OFF")!=NULL)

{

IOSET1=led2;

LCD_COMMAND(0X01);

LCD_STR("LIGHT OFF");

}


else if(strstr(buffer,"ALL ON")!=NULL)

{

IOSET1=mr1;

IOCLR1=mr2;

IOCLR1 |=led1|led2;

LCD_COMMAND(0X01);

LCD_STR("ALL ON");

}


else if(strstr(buffer,"ALL OFF")!=NULL)

{

IOCLR1=mr1;

IOCLR1=mr2;

IOSET1 |=led1|led2;

LCD_COMMAND(0X01);

LCD_STR("ALL OFF");

}


else

{

LCD_STR("Invalid cmd....");

}

}

}


 void LCD_INIT(void)
{
  PINSEL0=0;
IODIR0=LCD_D|RS|E;
LCD_COMMAND(0x01);
LCD_COMMAND(0x02);
LCD_COMMAND(0x0C);
LCD_COMMAND(0x28);
LCD_COMMAND(0x80);

}
void LCD_COMMAND(unsigned char cmd)
{
 IOCLR0=LCD_D;
IOSET0=(cmd&0xf0)<<10;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);                                                           (2);
IOCLR0=E;

IOCLR0=LCD_D;
IOSET0=(cmd&0x0f)<<14;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;

}
void LCD_DATA(unsigned char d)
{
IOCLR0=LCD_D;
IOSET0=(d&0xf0)<<10;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;

IOCLR0=LCD_D;
IOSET0=(d&0x0f)<<14;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;

}
void LCD_STR(unsigned char* s)
{
unsigned char count=0;
while(*s)
{
LCD_DATA(*s++);
count++;
if(count==16)
LCD_COMMAND(0xC0);
}  

}

// --- UART0 Configuration Functions ---
void UART0_CONFIG(void)
{
    PINSEL0 = 0x00000005; 
    U0LCR = 0x83; 
    U0DLL = 97; 
    U0LCR = 0x03; 
}

void UART0_Tx(unsigned char ch)
{
    while((U0LSR & (1 << 5)) == 0); 
    U0THR = ch;
}

void UART0_STR(unsigned char *s)
{
	while(*s)

{

UART0_Tx(*s);

s++;

}
 }
unsigned char UART0_Rx(void)
{
    while((U0LSR & (1 << 0)) == 0); 
    return U0RBR;
}

// --- GSM Modem Initialization ---
void GSM_INIT(void)
{
    UART0_STR("AT\r\n");
    delay_ms(100);
    
    UART0_STR("AT+CMGF=1\r\n"); 
    delay_ms(100);
    
    UART0_STR("AT+CNMI=2,2,0,0,0\r\n"); 
    delay_ms(100);
}
void GSM_SEND_SMS(void )

{

UART0_STR("AT+CMGS=\"+919876543210\"\r\n");

delay_ms(300);


UART0_STR("GSM TEST");

 delay_ms(300);

UART0_Tx(0X1A);


}


 void delay_ms(unsigned int ms)
 {
T0PR=15000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0X03;
T0TCR=0X00;

}


