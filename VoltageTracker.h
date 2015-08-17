
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
  void mode(byte mode)
  {
    pinMode(pin_, mode);
  }
  void measure(bool preRead = true)
  {
    if (preRead)
      analogRead(pin_);
    word v = analogRead(pin_);
    v_ = v_ - getValue() + v;
  }
  word getValue(byte extraBits = 0) const
  {
    return v_ >> (MEASURE_EXTRA_BITS - extraBits);
  }
  void sprint(char* buf) const
  {
  #if PRECISE_VOLTAGE
    word v = getValue(PRESENT_EXTRA_BITS);
    word v1000 = (word)((long)v * 5 * 1000 / ((1 << (10 + PRESENT_EXTRA_BITS)) - 1));
  #else
    word v = getValue();
    word v1000 = v * 5;
  #endif
    sprintf(buf, "%uv%03u", v1000 / 1000, v1000 % 1000);
  }
};
