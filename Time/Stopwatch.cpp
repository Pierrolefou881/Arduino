#include "Stopwatch.hpp"

/**
 * Updates the TimeData member _time_stamp only if this
 * Stopwatch is active, i.e. it has been started.
 * @param tick_duration_ms time elapsed since last call in milliseconds.
 */
void Time::Stopwatch::update_time_stamp(unsigned long tick_duration_ms)
{
  if (is_active)
  {
    Time::BaseClock::update_time_stamp(tick_duration_ms);
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
  set_time_stamp(Time::TimeData{ });
}

/**
 * @return true if this Stopwatch is ticking, false otherwise.
 */
bool Time::Stopwatch::is_running(void) const
{
  return is_active;
}