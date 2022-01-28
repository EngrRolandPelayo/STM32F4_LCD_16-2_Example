
#include "LCD.h"

//-----[ Alphanumeric LCD 16x2 Routines ]-----
void LCD_DATA(unsigned char Data)
{
    if(Data & 1) 
        HAL_GPIO_WritePin(D4_PORT, D4, GPIO_PIN_SET);
    	//D4 = 1;
    else
    	HAL_GPIO_WritePin(D4_PORT, D4, GPIO_PIN_RESET);
        //D4 = 0;
    if(Data & 2)
    	HAL_GPIO_WritePin(D5_PORT, D5, GPIO_PIN_SET);
        //D5 = 1;
    else
    	HAL_GPIO_WritePin(D5_PORT, D5, GPIO_PIN_RESET);
        //D5 = 0;
    if(Data & 4)
    	HAL_GPIO_WritePin(D6_PORT, D6, GPIO_PIN_SET);
        //D6 = 1;
    else
    	HAL_GPIO_WritePin(D6_PORT, D6, GPIO_PIN_RESET);
        //D6 = 0;
    if(Data & 8) 
    	HAL_GPIO_WritePin(D7_PORT, D7, GPIO_PIN_SET);
        //D7 = 1;
    else
    	HAL_GPIO_WritePin(D7_PORT, D7, GPIO_PIN_SET);
        //D7 = 0;
}
void LCD_CMD(unsigned char CMD)
{
    // Select Command Register
    HAL_GPIO_WritePin(RS_PORT, RS, GPIO_PIN_RESET);
	// RS = 0;
    // Move The Command Data To LCD
    LCD_DATA(CMD);
    // Send The EN Clock Signal
    HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_SET);
    // EN  = 1;
    __delay_us(500);
    HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_RESET);
    //EN  = 0;
}
void LCD_Clear()
{
    LCD_CMD(0);
    LCD_CMD(1);
}
void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
    unsigned char Temp,Low4,High4;
    if(r == 1)
    {
      Temp  = 0x80 + c - 1; //0x80 is used to move the cursor
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_CMD(High4);
      LCD_CMD(Low4);
    }
    if(r == 2)
    {
      Temp  = 0xC0 + c - 1;
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_CMD(High4);
      LCD_CMD(Low4);
    }
}
void LCD_Init()
{
  // IO Pin Configurations
  //LCD_DATA_PORT_D = 0x00;
  //LCD_RS_D = 0;
  //LCD_EN_D = 0;
  HAL_GPIO_WritePin(D4_PORT, D4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D5_PORT, D5, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D6_PORT, D6, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D7_PORT, D7, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RS_PORT, RS, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_RESET);
  // The Init. Procedure As Described In The Datasheet
  LCD_DATA(0x00);
  __delay_ms(30);
  __delay_us(500);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(150);
  LCD_CMD(0x03); 
  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}
void LCD_Write_Char(char Data)
{
   char Low4,High4;
   Low4  = Data & 0x0F;
   High4 = Data & 0xF0;
   HAL_GPIO_WritePin(RS_PORT, RS, GPIO_PIN_SET);
   //RS = 1;
   LCD_DATA(High4>>4);  
   HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_SET);
   //EN = 1;
   __delay_us(500);
   HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_RESET);
   //EN = 0;
   __delay_us(500);
   LCD_DATA(Low4); 
   HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_SET);
   //EN = 1;
   __delay_us(500);
   HAL_GPIO_WritePin(EN_PORT, EN, GPIO_PIN_RESET);
   //EN = 0;
   __delay_us(500);
}
void LCD_Write_String(char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
       LCD_Write_Char(str[i]);
}
void LCD_SL()
{
    LCD_CMD(0x01);
    LCD_CMD(0x08);
}
void LCD_SR()
{
    LCD_CMD(0x01);
    LCD_CMD(0x0C);
}

void __delay_ms(uint32_t Delay)
{
	HAL_Delay(Delay);
}

void __delay_us(uint32_t Delay)
{
	HAL_Delay(Delay / 1000);
}
