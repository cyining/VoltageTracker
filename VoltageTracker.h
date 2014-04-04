
#define PRECISE_VOLTAGE         1 // Precise voltage estimate by division

#define MEASURE_EXTRA_BITS      4 // Extra precision bits during measurement

#define PRESENT_EXTRA_BITS      3 // Extra precision bits during presentation

class VoltageTracker
{
protected:
  byte pin_;
  word v_;
public:
  VoltageTracker(byte pin)
  {
    pin_ = pin;
    v_ = 0;
  }
  void measure()
  {
    pinMode(pin_, INPUT);
    word v = analogRead(pin_);
    v_ = v_ - getVoltage() + v;
  }
  word getVoltage(byte extraBits = 0)
  {
    return v_ >> (MEASURE_EXTRA_BITS - extraBits);
  }
  void sprint(char* buf)
  {
  #if PRECISE_VOLTAGE
    word v = getVoltage(PRESENT_EXTRA_BITS);
    word v1000 = (word)((long)v * 5 * 1000 / ((1 << (10 + PRESENT_EXTRA_BITS)) - 1));
  #else
    word v = getVoltage();
    word v1000 = v * 5;
  #endif
    sprintf(buf, "%uv%03u", v1000 / 1000, v1000 % 1000);
  }
};