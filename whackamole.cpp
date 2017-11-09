#include "mbed.h"
#include "rtos.h"
#include "DebounceIn.h"
#include "TextLCD.h"

TextLCD lcd(p15, p16, p17, p18, p19, p20);

DigitalOut led1(p11);
DigitalOut led2(p8);
DigitalOut led3(p6);
DigitalOut led4(p10);
DigitalOut led5(p7);
DigitalOut led6(p5);

DebounceIn pb1(p23);
DebounceIn pb2(p22);
DebounceIn pb3(p21);
DebounceIn pb4(p26);
DebounceIn pb5(p24);
DebounceIn pb6(p25);
int n, c;
int comm;
int counter=0;
int timer=30;

//*clock counts down from 30 seconds*//
void Countdown(void const *args) {
    lcd.cls();
    while(true) {
        lcd.cls();
        lcd.printf("Time Left: %d s", timer);
        lcd.printf("\nHit Count: %d", counter);
        timer--;
        Thread::wait(1000);
    }
}

//*randomly selects which LEDs will turn on *//
void Random(void const *args) {
    n=0;
    
    while(true) {
        comm=rand()%15; //determines which LEDs will turn on
        c=rand()%400; //speed
        
        if(comm==0) {
            led1=1;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==1) {
            led1=0;
            led2=1;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==2) {
             led1=0;
            led2=0;
            led3=1;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==3) {
            led1=0;
            led2=0;
            led3=0;
            led4=1;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==4) {
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            led5=1;
            led6=0;
            wait(0.7);
        } else if (comm==5) {
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=1;
            wait(0.7);
        } else if (comm==6) {
            led1=1;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==7) {
             led1=0;
            led2=0;
            led3=1;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==8) {
            led1=0;
            led2=0;
            led3=0;
            led4=1;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==9) {
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            led5=1;
            led6=0;
            wait(0.7);
        } else if (comm==10) {
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=1;
            wait(0.7);
        } else if (comm==11) {
            led1=1;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==12) {
            led1=0;
            led2=1;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==13) {
           led1=0;
            led2=0;
            led3=1;
            led4=0;
            led5=0;
            led6=0;
            wait(0.7);
        } else if (comm==14) {
             led1=0;
            led2=0;
            led3=0;
            led4=1;
            led5=0;
            led6=0;
            wait(0.7);
        }
        n++;
        Thread::wait(c);
    }
}

//*if the correct button is pressed while the corresponding LED is on, the hit count will increase*//
void ButtonPress(void const *args) {   
    while(true) {
        if(led1==1&&pb1==0) {
            counter++;
        } else if(led2==1&&pb2==0) {
            counter++;
        } else if(led3==1&&pb3==0) {
            counter++;
        } else if(led4==1&&pb4==0) {
            counter++;
        } else if(led5==1&&pb5==0) {
            counter++;
        } else if(led6==1&&pb6==0) {
            counter++;
        }
        Thread::wait(300);
    }        
}

int main() {
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    pb5.mode(PullUp);
    pb6.mode(PullUp);
    wait(.001);
    
    Thread t3(Countdown);
    Thread t1(Random);
    Thread t2(ButtonPress);

    while(1) {
        if(timer==0) {
            lcd.cls();
            t1.terminate();
            t2.terminate();
            t3.terminate();
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            led5=0;
            led6=0;
            lcd.printf("Game Over!\nFinal score: %d", counter);
        }
        Thread::wait(1000);
    }
}
