

/*
 * Mega + expansion RAM + funky status LED,
 *
 * IMPORTANT! PLEASE USE Arduino 1.0.5 or better!
 * Older versions HAVE MAJOR BUGS AND WILL NOT WORK AT ALL!
 * Use of gcc-avr and lib-c that is newer than the Arduino version is even better.
 *
 * This program tests multitasking in xmem2.
 *
 * Note! Since the primary task (0) services serial in main(),
 * it may look like it is not getting a fair share of CPU time. It is.
 * Expect to see less 'L' printed! Also expect way less 'B' since that tests
 * the Sleep() function.
 *
 */

#include <avr/pgmspace.h>
#include <xmem.h>
#include <avrpins.h>
#include <stdio.h>

#define led 13

// Uncomment to test xmem::Sleep()
//#define TEST_TIMING

static FILE mystdout;
volatile int brightness = 128; // how bright the LED is
volatile int fadeAmount = 8; // how many points to fade the LED by

extern "C" unsigned int freeHeap();

// Fun! Serial stuff is thread safe!

static int my_putc(char c, FILE *t) {
        Serial.write(c);
}

void loop() {
        // Look mom! No hands!
#ifndef TEST_TIMING
        printf("L");
#endif
}


// tasks

void task_A(void) {
        for (;;) {
#ifndef TEST_TIMING
                printf("A");
#endif
        }
}

void task_B(void) {
        for (;;) {
#ifdef TEST_TIMING
                uint32_t x = millis();
                while (x == millis());
                x = millis();
                xmem::Sleep(30);
                uint32_t y = millis();
                printf("%i\r\n", y - x);
#else
                printf("B");
                xmem::Sleep(30);
#endif
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

void task_C(void) {
        for (;;) {
#ifndef TEST_TIMING
                printf("C");
#endif
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
        // The values t[1-3] are thrown out. You can save them to a global if you need to.

        uint8_t t1 = xmem::SetupTask(task_A);
        xmem::StartTask(t1);
        uint8_t t2 = xmem::SetupTask(task_B);
        xmem::StartTask(t2);
        uint8_t t3 = xmem::SetupTask(task_C);
        xmem::StartTask(t3);
}


