#include <Wire.h>
#define OLED_ADDR (0x3C) //OLED address 製品に記載の数値は7bitなので、8bitに変換して1bit右へずらした値(78>>3c)
  
byte DotB1[8]=
{
  B11111111,
  B00000111,
  B11111111,
  B00000011,
  B00000101,
  B00001001,
  B00010001,
  B00100001
};
  
void setup()
{
  Wire.begin();
  setup_i2c();
  Display_Black();
}
  
void loop()
{
  Display_Picture();
}
 
void setup_i2c()
{
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(B00000000); //control byte, Co bit = 0 (continue), D/C# = 0 (command)
    Wire.write(0xAE); //display off
    Wire.write(0xA8); //Set Multiplex Ratio  0xA8, 0x3F
      Wire.write(B00111111); //64MUX
    Wire.write(0xD3); //Set Display Offset 0xD3, 0x00
      Wire.write(0x00);
    Wire.write(0x40); //Set Display Start Line 0x40
    Wire.write(0xA0); //Set Segment re-map 0xA0/0xA1
    Wire.write(0xC0); //Set COM Output Scan Direction 0xC0,/0xC8
    Wire.write(0xDA); //Set COM Pins hardware configuration 0xDA, 0x02
      Wire.write(B00010010);
    Wire.write(0x81); //Set Contrast Control 0x81, 0x7F（明るさ設定）
      Wire.write(255); //0-255
    Wire.write(0xA4); //Disable Entire Display On（ディスプレイ全体ＯＮ）
    Wire.write(0xA6); //Set Normal Display 0xA6, Inverse display 0xA7
    Wire.write(0xD5); //Set Display Clock Divide Ratio/Oscillator Frequency 0xD5, 0x80
      Wire.write(B10000000);
    Wire.write(0x2E); //Deactivate scrollスクロール表示解除
    Wire.write(0x20); //Set Memory Addressing Mode
      Wire.write(0x10); //Page addressing mode
    Wire.write(0x21); //set Column Address
      Wire.write(0); //Column Start Address←水平開始位置はここで決める(0～127)
      Wire.write(127); //Column Stop Address　画面をフルに使う
    Wire.write(0x22); //Set Page Address
      Wire.write(0); //垂直開始位置（ページ）
      Wire.write(7); //垂直終了位置（ページ）
    Wire.write(0x8D); //Set Enable charge pump regulator 0x8D, 0x14
      Wire.write(0x14);
    Wire.write(0xAF); //Display On 0xAF
  Wire.endTransmission();
}
 
void Display_Black()
{
  byte i, j, k;
 
  for(i = 0; i < 8; i++)
  {//8ページ分塗りつぶす
    Wire.beginTransmission(OLED_ADDR);
      Wire.write(B10000000); //control byte, Co bit = 1 (One command only), D/C# = 0 (command)
      Wire.write(0xB0 | i); //set page start address←垂直開始位置はここで決める8bitで１ページ(B0～B7)
    Wire.endTransmission();
     
    for(j = 0; j < 16; j++)
    {//column = 8byte x 16 ←8バイト毎に水平に連続で16個表示
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(B01000000); //control byte, Co bit = 0 (continue), D/C# = 1 (data)
      for(k = 0; k < 8; k++)
      { //なぜか一気に128列まで出力できなかったので、8byte毎にした
        Wire.write(0x00);
      }
      Wire.endTransmission();
    }
    yield();
  }
}
 
void Display_Picture(){
  byte i,j,k;
  byte on_off; //画面の白黒　塗り替え数値
  for(on_off = 0; on_off < 2; on_off++)
  {
    for(i=0; i<8; i++)
    {
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(B00000000); //control byte, Co bit = 0 (continue), D/C# = 0 (command)
      Wire.write(0xB0 | i); //set page start address←垂直開始位置はここで決める(B0～B7)
      Wire.write(0x21);//set column addres
      Wire.write(0x00 | 0);//start column addres←水平開始位置はここで決める(0～126)
      Wire.write(B01111111);//Column Stop Address　画面をフルに使う
      Wire.endTransmission();
      for(j=0; j<16; j++)
      {//column = 8byte x 16 ←8バイト毎に水平に連続で16個表示
        Wire.beginTransmission(OLED_ADDR);
        Wire.write(B01000000); //control byte, Co bit = 0 (continue), D/C# = 1 (data)
        if(on_off == 1)
        {
          for(k=0; k<8; k++)
          {
            Wire.write(0x00); //黒画面に塗り替え
          }
        }
        else
        {
          for(k=0; k<8; k++)
          {
            Wire.write(DotB1[k]);
          }
        }
        Wire.endTransmission();
      }
    }
    delay(1000); //1秒ごとに画面を塗り替え
  }
}
