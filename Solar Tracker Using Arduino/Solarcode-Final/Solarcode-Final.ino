#include <Servo.h>

Servo servohori; // horizontal servo (BOTTOM SERVO)
int servoh = 0;
int servohLimitHigh = 180;
int servohLimitLow = 10;

Servo servoverti; // vertical servo (TOP SERVO)
int servov = 0;
int servovLimitHigh = 180;
int servovLimitLow = 10;

int ldrtopr = 1;
int ldrtopl = 2;

int ldrbotr = 0;
int ldrbotl = 3;

void setup()
{
    servohori.attach(10);
    servohori.write(0);

    servoverti.attach(9);
    servoverti.write(0);

    Serial.begin(9600); // Initialize serial communication
    delay(500);
}

void loop()
{
    servoh = servohori.read();
    servov = servoverti.read();

    int topl = analogRead(ldrtopl);
    int topr = analogRead(ldrtopr);
    int botl = analogRead(ldrbotl);
    int botr = analogRead(ldrbotr);

    int avgtop = (topl + topr) / 2;
    int avgbot = (botl + botr) / 2;
    int avgleft = (topl + botl) / 2;
    int avgright = (topr + botr) / 2;

    if (avgtop > avgbot)
    {
        servoverti.write(servov - 1);
        if (servov > servovLimitHigh)
        {
            servov = servovLimitHigh;
        }
        Serial.println("Moving up");
        delay(8);
    }
    else if (avgbot > avgtop)
    {
        servoverti.write(servov + 1);
        if (servov < servovLimitLow)
        {
            servov = servovLimitLow;
        }
        Serial.println("Moving down");
        delay(8);
    }
    else
    {
        servoverti.write(servov);
    }

    if (avgleft > avgright)
    {
        servohori.write(servoh - 1);
        if (servoh > servohLimitHigh)
        {
            servoh = servohLimitHigh;
        }
        Serial.println("Moving left");
        delay(8);
    }
    else if (avgright > avgleft)
    {
        servohori.write(servoh + 1);
        if (servoh < servohLimitLow)
        {
            servoh = servohLimitLow;
        }
        Serial.println("Moving right");
        delay(8);
    }
    else
    {
        servohori.write(servoh);
    }

    delay(50);
}