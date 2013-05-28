

/*
 * Mega + expansion RAM + funky status LED,
 *
 * IMPORTANT! PLEASE USE Arduino 1.0.5 or better!
 * Older versions HAVE MAJOR BUGS AND WILL NOT WORK AT ALL!
 * Use of gcc-avr and lib-c that is newer than the Arduino version is even better.
 *
 * This program tests multitasking in xmem2.
 *
 */

#include <avr/pgmspace.h>
#include <xmem.h>
#include <avrpins.h>
#include <stdio.h>
static FILE mystdout;

#define led 13
volatile int brightness = 128; // how bright the LED is
volatile int fadeAmount = 8; // how many points to fade the LED by
volatile uint32_t LEDnext_time; // fade timeout

extern "C" unsigned int freeHeap();

// Fun! Serial stuff is thread safe!
static int my_putc(char c, FILE *t) {
        Serial.write(c);
}

void loop() {
        // Look mom! No hands!
        printf("L");
}


// tasks

void task_A(void) {
        for (;;) {
                printf("A");
        }
}

void breath(void) {
        for (;;) {
                printf("B");
                if (millis() >= LEDnext_time) {
                        LEDnext_time = millis() + 30;

                        // set the brightness of pin 9:
                        analogWrite(led, brightness);

                        // change the brightness for next time through the loop:
                        brightness = brightness + fadeAmount;

                        // reverse the direction of the fading at the ends of the fade:
                        if (brightness <= 0) {
                                brightness = 0;
                                fadeAmount = -fadeAmount;
                        }
                        if (brightness >= 255) {
                                brightness = 255;
                                fadeAmount = -fadeAmount;
                        }
                }
        }
}

void setup() {
        // declare pin 9 to be an output:
        pinMode(led, OUTPUT);
        analogWrite(led, 0);
        pinMode(2, OUTPUT);
        mystdout.put = my_putc;
        mystdout.get = NULL;
        mystdout.flags = _FDEV_SETUP_WRITE;
        mystdout.udata = 0;
        stdout = &mystdout;
        Serial.begin(115200);

        // Note! tasks do NOT actually start here. They start after the return to main()!

        uint8_t t1 = xmem::SetupTask(breath);
        xmem::StartTask(t1);
        uint8_t t2 = xmem::SetupTask(task_A);
        xmem::StartTask(t2);
        LEDnext_time = millis() - 1;


}


