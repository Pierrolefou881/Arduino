#include "Stopwatch.hpp"

/**
 * Updates the TimeData member _time_stamp only if this
 * Stopwatch is active, i.e. it has been started.
 * @param tick_time_ms system clock time since power on in milliseconds.
 */
void Time::Stopwatch::tick(unsigned long tick_time_ms)
{
  if (is_active)
  {
    Time::BaseClock::tick(tick_time_ms);
  }
}

/**
 * Activates this Stopwatch and starts time update.
 */
void Time::Stopwatch::start(void)
{
  is_active = true;
}

/**
 * Deactivates this Stopwatch's time update.
 */
void Time::Stopwatch::stop(void)
{
  is_active = false;
}

/**
 * Resets this Stopwatch's _time_stamp member to 00:00:00:000
 */
void Time::Stopwatch::reset(void)
{
  set_time_stamp(Time::TimeData{});
}