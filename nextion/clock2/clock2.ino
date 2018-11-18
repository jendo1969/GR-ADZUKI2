
#include "Nextion.h"
#include "NexTouch.h"
#include <RTC.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

#define BME_SCK  30
#define BME_MISO 29
#define BME_MOSI 28
#define BME_CS   27

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

float Temp;
float Pres;
float Humi;
float Alti;
float old_Temp;
float old_Pres;
float old_Humi;
float old_Alti;

RTC rtc;
int year, mon, day, hour, min, sec, week;
int old_day, old_sec;
//String timeString = "";
char timeBuff[10];
char input[64];
char buff[64];
int i;
char wk[][4] = {
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat"
};

//PAGE0
NexPage page0 = NexPage(0, 0, "page0");
NexPicture p01 = NexPicture(0, 1, "p01");
NexText t00 = NexText(0, 2, "t00");
NexPicture p02 = NexPicture(0, 3, "p02");
NexPicture p00 = NexPicture(0, 4, "p00");
NexText t01 = NexText(0, 5, "t01");
NexText t02 = NexText(0, 6, "t02");
NexText t03 = NexText(0, 7, "t03");
NexText t04 = NexText(0, 8, "t04");
NexText t05 = NexText(0, 9, "t05");
NexText t06 = NexText(0, 10, "t06");
NexText t08 = NexText(0, 12, "t08");
NexText t09 = NexText(0, 13, "t09");
NexText t010 = NexText(0, 14, "t010");

//PAGE1
NexPage page1 = NexPage(1, 0, "page1");
NexText t10 = NexText(1, 1, "t10");
NexTouch qr10 = NexTouch(1, 2, "qr10");
NexPicture p10 = NexPicture(1, 3, "p10");

//PAGE2
NexPage page2 = NexPage(2, 0, "page2");
NexPicture p20 = NexPicture(2, 1, "p20");
NexText t20 = NexText(2, 2, "t20");
NexButton b20 = NexButton(2, 3, "b20");
NexText t21 = NexText(2, 4, "t21");
NexText t22 = NexText(2, 5, "t22");
NexText t23 = NexText(2, 6, "t23");
NexText t24 = NexText(2, 7, "t24");
NexText t25 = NexText(2, 8, "t25");
NexText t26 = NexText(2, 9, "t26");
NexText t27 = NexText(2, 10, "t27");
NexText t28 = NexText(2, 11, "t28");

char buffer[100] = {0};
NexTouch *nex_listen_list[] = 
{
    &page0,
    &p01,
    &t00,
    &p02,
    &p00,
    &t01,
    &t02,
    &t03,
    &t04,
    &t05,
    &t06,
    &t08,
    &t09,
    &t010,
    
    &page1,
    &t10,
    &qr10,
    &p10,

    &page2,
    &p20,
    &t20,
    &b20,
    &t21,
    &t22,
    &t23,
    &t24,
    &t25,
    &t26,
    &t27,
    &t28,

    NULL
};

int zeller(int y, int m, int d)
{
    int h;
    if(m < 3)
    {
        y--;
        m+=12;
    }
    h = (y + y/4 - y/100 + y/400 + (13 * m + 8)/5 + d)%7;
    
    return h;
}

void b20PopCallback(void *ptr)
{
    int sy, sm, sd, sh, sn, ss, sw;
    
    memset(buffer, 0, sizeof(buffer));
    t23.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &sy);
    
    memset(buffer, 0, sizeof(buffer));
    t24.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &sm);

    memset(buffer, 0, sizeof(buffer));
    t25.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &sd);

    memset(buffer, 0, sizeof(buffer));
    t26.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &sh);

    memset(buffer, 0, sizeof(buffer));
    t27.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &sn);

    memset(buffer, 0, sizeof(buffer));
    t28.getText(buffer, sizeof(buffer));
    sscanf(buffer, "%d", &ss);
    
    if((sy < 2000) || (sy > 2100))
    {
        return;
    }
    if((sm < 1) || (sm > 12))
    {
        return;
    }
    if((sm == 1) || (sm == 3) || (sm == 5) || (sm == 7) || (sm == 8) || (sm == 10) || (sm == 12)) 
    {
        if((sd < 1) || (sd > 31))
        {
            return;
        }
    }
    else if((sm == 4) || (sm == 6) || (sm == 9) || (sm == 11)) 
    {
        if((sd < 1) || (sd > 30))
        {
            return;
        }
    }
    else
    {
        if((sd < 1) || (sd > 29))
        {
            return;
        }
    }
    if((sh < 0) || (sh > 23))
    {
        return;
    }
    if((sn < 0) || (sn > 59))
    {
        return;
    }
    if((ss < 0) || (ss > 59))
    {
        return;
    }
 
    sw = zeller(sy, sm, sd);
    rtc.setDateTime(sy, sm, sd, sh, sn, ss, sw);

    old_day = 0;
    old_sec = 0;
    
    page0.show();
}

void p01PopCallback(void *ptr)
{
    page2.show();
      
    sprintf(timeBuff, "%04d", year);
    t23.setText(timeBuff);
    sprintf(timeBuff, "%02d", mon);
    t24.setText(timeBuff);
    sprintf(timeBuff, "%02d", day);
    t25.setText(timeBuff);
    
    sprintf(timeBuff, "%02d", hour);
    t26.setText(timeBuff);
    sprintf(timeBuff, "%02d", min);
    t27.setText(timeBuff);
    sprintf(timeBuff, "%02d", sec);
    t28.setText(timeBuff);
    
    old_day = 0;
    old_sec = 0;
}

void p0PopCallback(void *ptr)
{
    old_day = 0;
    old_sec = 0;
    page0.show(); 
}

void setup(void)
{
    old_day = 0;
    old_sec = 0;
  
    // Open serial communications and wait for port to open:
    Serial.begin(9600);

    bool status;
    status = bme.init();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    rtc.begin();
    rtc.setDateTime(2018, 9, 16, 0, 0, 0, RTC_WEEK_SUNDAY);
  
    nexInit();
    
    p01.attachPop(p01PopCallback);
    b20.attachPop(b20PopCallback);

    p10.attachPop(p0PopCallback);
    p20.attachPop(p0PopCallback);
    
    dbSerialPrintln("setup done");
}
void loop(void)
{
    Temp = bme.readTemperature();
    Pres = bme.readPressure() / 100.0F;
    Humi = bme.readHumidity();  
    Alti = bme.readAltitude(SEALEVELPRESSURE_HPA);  
  
    rtc.getDateTime(year, mon, day, hour, min, sec, week);
    year = 2000+year;

    if(old_sec != sec)
    {
        sprintf(timeBuff, "%02d:%02d:%02d", hour, min, sec);
        t00.setText(timeBuff);
        
        if(old_Temp != Temp)
        {
            sprintf(timeBuff, "%03.1f", Temp);
            t03.setText(timeBuff);
        }
       if(old_Humi != Humi)
       {
           sprintf(timeBuff, "%03.1f", Humi);
           t04.setText(timeBuff);
       }
       if(old_Pres != Pres)
       {
           sprintf(timeBuff, "%03.1f", Pres);
           t05.setText(timeBuff);
       }
       if(old_Alti != Alti)
       {
           sprintf(timeBuff, "%03.1f", Alti);
           t06.setText(timeBuff);
       }
       old_Temp = Temp;
       old_Pres = Pres;
       old_Humi = Humi;  
       old_Alti = Alti;  
    }
    
    if(old_day != day)
    {
        sprintf(timeBuff, "%04d/%02d/%02d", year, mon, day);
        t01.setText(timeBuff);
    
        week = zeller(year, mon, day);
        switch(week)
        {
            case 0:
                t02.setText(wk[0]);
                break;
            case 1:
                t02.setText(wk[1]);
                break;
            case 2:
                t02.setText(wk[2]);
                break;
            case 3:
                t02.setText(wk[3]);
                break;
            case 4:
                t02.setText(wk[4]);
                break;
            case 5:
                t02.setText(wk[5]);
                break;
            case 6:
                t02.setText(wk[6]);
                break;
        }    
    }
    
    old_day = day;
    old_sec = sec;
    
    if (Serial.available() > 0) 
    {
        // get incoming byte:
        input[i] = Serial.read();

        // 文字数が2以上 or 末尾文字
        if (input[i] == ';')
        {
            // 末尾に終端文字の挿入
            input[i] = '\0';
            if((i==16) && (input[0]=='T'))
            {   //01234567890123456
                //T201807212232006;
                sscanf(&input[1],"%04d%02d%02d%02d%02d%02d%d", &year, &mon, &day, &hour, &min, &sec, &week);
                rtc.setDateTime(year, mon, day, hour, min, sec, week);
                sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d %d\r", year, mon, day, hour, min, sec, week);
                Serial.println(buff);
            }
            else if((i==2) && (input[0]=='T') && (input[1]=='?'))
            {
                sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d %d\r", year, mon, day, hour, min, sec, week);
                Serial.println(buff);
            }
            // カウンタの初期化
            i = 0;
        }
        else
        {
            i++;
        }
    }
 
    nexLoop(nex_listen_list);
}
