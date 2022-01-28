
#define RS GPIO_PIN_6 //PE_0
#define RS_PORT GPIOE
#define EN GPIO_PIN_8 //PB_8
#define EN_PORT GPIOB
#define D4 GPIO_PIN_6 //PB_6
#define D4_PORT GPIOB
#define D5 GPIO_PIN_3 //PB_3
#define D5_PORT GPIOB
#define D6 GPIO_PIN_6 //PD_6
#define D6_PORT GPIOD
#define D7 GPIO_PIN_2 //PD_2
#define D7_PORT GPIOD

#include "stm32f4xx_hal.h"
//==========================================
//-----[ Prototypes For All Functions ]-----

void LCD_Init();  // Initialize The LCD For 4-Bit Interface
void LCD_Clear(); // Clear The LCD Display
void LCD_SL();    // Shift The Entire Display To The Left
void LCD_SR();    // Shift The Entire Display To The Right

void LCD_CMD(unsigned char);   // Send Command To LCD
void LCD_DATA(unsigned char);  // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char);  // Set Cursor Position
void LCD_Write_Char(char);     // Write Character To LCD At Current Position
void LCD_Write_String(char*);  // Write A String To LCD

void __delay_us(uint32_t Delay);
void __delay_ms(uint32_t Delay);
//------------------------------------------
