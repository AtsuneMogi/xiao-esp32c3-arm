#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <AsyncUDP.h>
#include <WiFi.h>
#include <Wire.h>

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)


char buf[1];
char ssid[] = "M5StickC-Controller";
char pass[] = "controller";
AsyncUDP udp; // udp instance
unsigned int port = 8888; // local port to listen on


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

uint8_t servonum = 0;
uint16_t servo0pulse = 0;
uint16_t servo1pulse = 0;
bool grub = false;


void setup() {
    Serial.begin(115200);
    Serial.println("Servo Test");

    pwm.begin();
    pwm.setPWMFreq(60);  // Analog servos run at ~50 Hz updates
    delay(100);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    delay(100);

    if (udp.listen(port)) {
        udp.onPacket([](AsyncUDPPacket packet) {
            buf[0] = (char)*(packet.data());
            Serial.print(buf);
        });
    }
}


void loop() {
    /*for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) // Drives each servo one at a time first                                                                                                
        pwm.setPWM(servonum, 0, pulselen); // to maximum pulse length then to minimum pulse length.
    delay(300);
    for (int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--)
        pwm.setPWM(servonum, 0, pulselen);
    delay(300);
    Serial.println("Success!");
    servonum++; // Proceeds to next servo.
    if (servonum > 4) servonum = 0;*/
    switch (buf[0]) {
        case 'a':
            if (servo1pulse + 50 < SERVOMAX) {
                for (int i = 0; i < 50; i++) {
                    servo1pulse++;
                    pwm.setPWM(1, 0, servo1pulse);
                    delay(10);
                }
            }
            break;
        case 'A':
            if (servo1pulse + 100 < SERVOMAX) {
                for (int i = 0; i < 100; i++) {
                    servo1pulse++;
                    pwm.setPWM(1, 0, servo1pulse);
                    delay(10);
                }
            }
            break;
        case 'b':
            if (SERVOMIN < servo1pulse - 50) {
                for (int i = 0; i < 50; i++) {
                    servo1pulse--;
                    pwm.setPWM(1, 0, servo1pulse);
                    delay(10);
                }
            }
            break;
        case 'B':
            if (SERVOMIN < servo1pulse - 100) {
                for (int i = 0; i < 100; i++) {
                    servo1pulse--;
                    pwm.setPWM(1, 0, servo1pulse);
                    delay(10);
                }
            }
            break;
        case 'c':
            break;
        case 'C':
            break;
        case 'd':
            break;
        case 'D':
            break;
        case 'e':
            break;
        case 'E':
            break;
        case 'f':
            break;
        case 'F':
            break;
        case 'g':
            if (SERVOMIN < servo0pulse - 50) {
                for (int i = 0; i < 50; i++) {
                    servo0pulse--;
                    pwm.setPWM(0, 0, servo0pulse);
                    delay(10);
                }
            }
            break;
        case 'G':
            if (SERVOMIN < servo0pulse - 100) {
                for (int i = 0; i < 50; i++) {
                    servo0pulse--;
                    pwm.setPWM(0, 0, servo0pulse);
                    delay(10);
                }
            }
            break;
        case 'h':
            if (servo0pulse + 50 < SERVOMAX) {
                for (int i = 0; i < 50; i++) {
                    servo0pulse++;
                    pwm.setPWM(0, 0, servo0pulse);
                    delay(10);
                }
            }
            break;
        case 'H':
            if (servo0pulse + 100 < SERVOMAX) {
                for (int i = 0; i < 50; i++) {
                    servo0pulse++;
                    pwm.setPWM(0, 0, servo0pulse);
                    delay(10);
                }
            }
            break;
        case 'I':
            if (grub == false) {
                grub = true;
                for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) // Drives each servo one at a time first                                                                                                
                    pwm.setPWM(3, 0, pulselen); // to maximum pulse length then to minimum pulse length.
                delay(300);
            } else {
                grub = false;
                for (int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--)
                    pwm.setPWM(3, 0, pulselen);
                delay(300);
            }
            break;
        case 'J':
            break;
        case 'K':
            break;
        default:
            break;
    }
    delay(100);
}

