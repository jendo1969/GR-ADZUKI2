
#include "Nextion.h"

void p0PopCallback(void *ptr);
void t0PopCallback(void *ptr);
void b0PopCallback(void *ptr);
void b1PopCallback(void *ptr);
void p1PopCallback(void *ptr);

NexPage page0 = NexPage(0, 0, "page0");
NexText t0 = NexText(0, 1, "t0");
NexButton b0 = NexButton(0, 2, "b0");
NexButton b1 = NexButton(0, 3, "b1");
NexPicture p0 = NexPicture(0, 4, "p0");

NexPage page1 = NexPage(1, 0, "page1");
NexPicture p1 = NexPicture(1, 1, "p1");

char buffer[100] = {0};
NexTouch *nex_listen_list[] = 
{
    &p0,
    &t0,
    &b0,
    &b1,
    &p1,
    NULL
};

void p0PopCallback(void *ptr)
{
    dbSerialPrintln("page0PopCallback");
    page1.show();
}

void p1PopCallback(void *ptr)
{
    dbSerialPrintln("page1PopCallback");
    page0.show();
}

void t0PopCallback(void *ptr)
{
    dbSerialPrintln("t0PopCallback");
    t0.setText("50");
}
void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    
    dbSerialPrintln("b0PopCallback");
    memset(buffer, 0, sizeof(buffer));
    t0.getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number += 1;
    memset(buffer, 0, sizeof(buffer));
    //itoa(number, buffer, 10);
    sprintf(buffer, "%d", number);
    
    t0.setText(buffer);
}
void b1PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    
    dbSerialPrintln("b1PopCallback");
    memset(buffer, 0, sizeof(buffer));
    t0.getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number -= 1;
    memset(buffer, 0, sizeof(buffer));
    //itoa(number, buffer, 10);
    sprintf(buffer, "%d", number);
       
    t0.setText(buffer);
}
void setup(void)
{
    nexInit();
    
    p0.attachPop(p0PopCallback);
    p1.attachPop(p1PopCallback);
    
    t0.attachPop(t0PopCallback);
    b0.attachPop(b0PopCallback);
    b1.attachPop(b1PopCallback);
    dbSerialPrintln("setup done");
}
void loop(void)
{
    nexLoop(nex_listen_list);
}
