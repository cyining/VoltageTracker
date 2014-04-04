class TimeTracker
{
protected:
  unsigned long t_;
public:
  TimeTracker()
  {
    t_ = millis();
  }
  unsigned long getTime() const
  {
    return t_;
  }
  void next()
  {
    t_ += 1000;
  }
  bool ready(unsigned long t) const
  {
    return t > getTime();
  }
  void sprint(char* buf, unsigned long t) const
  {
    t /= 1000; // seconds
    byte ss = t % 60; // SS
    t /= 60; // minutes
    byte mm = t % 60; // MM
    t /= 60; // hours
    byte hh = t % 24; // HH
    t /= 24; // days
    byte dd = t; // DD
    String s;
    if (dd)
    {
      buf += sprintf(buf, "%ud", dd);
    }
    if (s.length() || hh)
    {
      buf += sprintf(buf, "%uh", hh);
    }
    if (s.length() || mm)
    {
      buf += sprintf(buf, "%um", mm);
    }
    sprintf(buf, "%us", ss);
  }
};
