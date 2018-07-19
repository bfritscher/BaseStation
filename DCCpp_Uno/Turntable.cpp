#include "Turntable.h"
#include "Arduino.h"

// if in EPROM?
// TODO loadInternalPostion();

Turntable::Turntable()
{
    //establish motor direction toggle pins
    pinMode(TURNTABLE_CH_A_DIR, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
    //establish motor brake pins
    pinMode(TURNTABLE_CH_A_BRAKE, OUTPUT); //brake (disable) CH A
    digitalWrite(TURNTABLE_CH_A_BRAKE, LOW);   //Disengage the Brake for Channel A
    // relay for move
    pinMode(TURNTABLE_RELAY_PIN, OUTPUT);
    switchOff();
    // sensor
    pinMode(A0, INPUT);
    Serial.println("Turntable init");
}

void Turntable::moveTo(int target)
{
    if (target == 99)
    {
        internalPosition = 0;
        currentTarget = 0;
        switchOff();
        setSpeed(TURNTABLE_OFF);
        return;
    }
    currentTarget = target;
    setSpeed(TURNTABLE_SLOW);
    switchOn(); // test if short enough for 1
    move();
}


void Turntable::check()
{
    // read analog sensor for change
    // if change
        //internalPosition += direction;
        //saveInternalPosition();
        //move();
    // Serial.println("Turntable V: " + String(analogRead(A0)));
}


void Turntable::move()
{
    int delta = currentTarget - internalPosition;
    // calculate shortest direction
    if (delta > 24)
    {
        delta = delta - 48;
    }
    if (delta < -24)
    {
        delta = delta + 48;
    }
    direction = delta >= 0 ? 1 : -1;
    if (direction > 0) {
        digitalWrite(TURNTABLE_CH_A_DIR, HIGH); //Establishes forward direction of Channel A
    } else {
        digitalWrite(TURNTABLE_CH_A_DIR, LOW); //Establishes backward direction of Channel A
    }
    delta = abs(delta);
    Serial.println("delta: " + String(delta) + " direction: " + String(direction));
    // speed based on distance
    if (delta == 0)
    {
        switchOff();
        // TODO timeout(setSpeed(TURNTABLE_OFF))
    }
    else if (delta == 1)
    {
        setSpeed(TURNTABLE_SLOW);
    }
    else if (delta >= 4)
    {
        setSpeed(TURNTABLE_FAST);
    }
    else
    {
        setSpeed(TURNTABLE_MEDIUM);
    }
}

void Turntable::setSpeed(int speed)
{
    analogWrite(TURNTABLE_CH_A_PWM, speed);   //Spins the motor on Channel A at speed
}

void Turntable::switchOn()
{
    digitalWrite(TURNTABLE_RELAY_PIN, LOW);
}

void Turntable::switchOff()
{
    digitalWrite(TURNTABLE_RELAY_PIN, HIGH);
}

Analog::Analog()
{

    //establish motor direction toggle pins
    pinMode(TURNTABLE_CH_B_DIR, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
    //establish motor brake pins
    pinMode(TURNTABLE_CH_B_BRAKE, OUTPUT); //brake (disable) CH A
    digitalWrite(TURNTABLE_CH_B_BRAKE, LOW);   //Disengage the Brake for Channel B
    Serial.println("analog init");
}

void Analog::set(int speed, int direction)
{
    Serial.println("analog speed:" + String(speed) + " direction: " + String(direction));
    // TODO: brakeing?
    if (direction == 1) {
        digitalWrite(TURNTABLE_CH_B_DIR, HIGH); //Establishes forward direction of Channel B
    } else {
        digitalWrite(TURNTABLE_CH_B_DIR, LOW); //Establishes backward direction of Channel B
    }
    analogWrite(TURNTABLE_CH_B_PWM, speed*255/128);
}
