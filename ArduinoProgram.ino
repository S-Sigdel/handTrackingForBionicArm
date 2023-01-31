#include <Servo.h>
#define numOfValsRec 6
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;
Servo servoWrist;

int valsRec[numOfValsRec];
//$00000
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;
void setup()
{
    Serial.begin(9600);
    servoThumb.attach(7);
    servoIndex.attach(9);
    servoMiddle.attach(11);
    servoRing.attach(8);
    servoPinky.attach(10);
    servoWrist.attach(13);
}
void receiveData()
{
    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '$')
        {
            counterStart = true;
        }
        if (counterStart)
        {
            if (counter < stringLength)
            {
                receivedString = String(receivedString + c);
                counter++;
            }
            if (counter >= stringLength)
            {
                for (int i = 0; i < numOfValsRec; i++)
                {
                    int num = (i * digitsPerValRec) + 1;
                    valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
                }
                receivedString = "";
                counter = 0;
                counterStart = false;
            }
        }
    }
}

void loop()
{
    receiveData();
    if (valsRec[0] == 1)
    {
        servoThumb.write(180);
    }
    else
    {
        servoThumb.write(0);
    }
    if (valsRec[1] == 0)
    {
        servoIndex.write(180);
    }
    else
    {
        servoIndex.write(0);
    }
    if (valsRec[2] == 0)
    {
        servoMiddle.write(180);
    }
    else
    {
        servoMiddle.write(0);
    }
    if (valsRec[3] == 0)
    {
        servoRing.write(180);
    }
    else
    {
        servoRing.write(0);
    }
    if (valsRec[4] == 0)
    {
        servoPinky.write(180);
    }
    else
    {
        servoPinky.write(0);
    }
    if (valsRec[5] == 0)
    {
        servoWrist.write(100);
    }
    else
    {
        servoWrist.write(0);
    }
}