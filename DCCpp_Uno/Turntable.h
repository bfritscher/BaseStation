#include "Arduino.h"

#ifndef Turntable_h
#define Turntable_h

#define TURNTABLE_CH_A_PWM 3
#define TURNTABLE_CH_A_DIR 12
#define TURNTABLE_CH_A_BRAKE 9
#define TURNTABLE_RELAY_PIN 22
#define TURNTABLE_SENSOR_PIN A8

#define TURNTABLE_OFF 0
#define TURNTABLE_SLOW 160 // 12 Volt
#define TURNTABLE_MEDIUM 200 // 14 Volt
#define TURNTABLE_FAST 240 // 18 Volt

class Turntable
{
    public:
        Turntable();
        void moveTo(int target);
        void check();
    private:
        void move();
        void setSpeed(int speed); // 0-255 % voltage
        void switchOn();
        void switchOff();
        int internalPosition = 0; // 0-48
        int direction = 1; // -1 || 1
        int currentTarget = 0; // 0-48
};

#define TURNTABLE_CH_B_PWM 11
#define TURNTABLE_CH_B_DIR 13
#define TURNTABLE_CH_B_BRAKE 9

class Analog
{
    public:
        Analog();
        void set(int speed, int direction);
};

#endif
