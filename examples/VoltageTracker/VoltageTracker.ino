#include "Arduino.h"
#include "VoltageTracker.h"
#include "TimeTracker.h"

VoltageTracker voltageTracker(A0);
TimeTracker timeTracker;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  voltageTracker.measure();
  unsigned long t = millis();
  if (timeTracker.ready(t))
  {
    char buf[16];
    voltageTracker.sprint(buf);
    Serial.print(buf);
    timeTracker.sprint(buf, t);
    Serial.print(' ');
    Serial.println(buf);
    timeTracker.next();
  }
}
