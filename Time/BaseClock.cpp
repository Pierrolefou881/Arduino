#include "BaseClock.hpp"
#include <limits.h>

const int Time::TimeData::MILLISECOND_TO_SECOND = 1000;
const int Time::TimeData::SECOND_MINUTE_HOUR = 60;
const int Time::TimeData::HOUR_TO_DAY = 24;

/**
 * Updates the _time_stamp member with additional tick
 * duration deduced from provided instant. Manages overflows.
 * @param tick_time_ms system clock time since power on in milliseconds.
 */
void Time::BaseClock::tick(unsigned long tick_time_ms)
{
  unsigned long tick_duration{ };
  // Overflow detected
  if (tick_time_ms < _last_tick)
  { 
    tick_duration = ULONG_MAX - _last_tick + tick_time_ms;
  }
  else
  {
    tick_duration = tick_time_ms - _last_tick;
  }

  _last_tick = tick_time_ms;
  update_time_stamp(tick_duration);
}

/**
 * @return the non non-mutable reference to the _time_stamp member.
 */
const Time::TimeData& Time::BaseClock::get_time_stamp(void) const
{
  return *_time_stamp;
}

/**
 * Replaces the _time_stamp member's value with the provided one.
 * @param time_stamp new value to assign to this BaseClock
 */
void Time::BaseClock::set_time_stamp(const Time::TimeData& time_stamp)
{
  _time_stamp = new TimeData{ time_stamp };
}

/**
 * Updates this BaseClock's _time_stamp member taking into account
 * the provided tick duration.
 * @param tick_duration_ms to add to the current TimeData.
 */
void Time::BaseClock::update_time_stamp(unsigned long tick_duration_ms)
{
  _time_stamp->millisecond += tick_duration_ms;

  // Check for a new second. If not, just return here.
  auto overflow = _time_stamp->millisecond / Time::TimeData::MILLISECOND_TO_SECOND;
  if (overflow <= 0)
  {
    return;
  }

  _time_stamp->second += overflow;
  _time_stamp->millisecond %= Time::TimeData::MILLISECOND_TO_SECOND;
  SecondElapsed->call(this, *_time_stamp);

  // Check for a new minute. If not, return here.
  overflow = _time_stamp->second / Time::TimeData::SECOND_MINUTE_HOUR;
  if (overflow <= 0)
  {
    return;
  }

  _time_stamp->minute += overflow;
  _time_stamp->second %= Time::TimeData::SECOND_MINUTE_HOUR;
  MinuteElapsed->call(this, *_time_stamp);

  // Check for a new hour. If not, return here.
  overflow = _time_stamp->minute / Time::TimeData::SECOND_MINUTE_HOUR;
  if (overflow <= 0)
  {
    return;
  }

  _time_stamp->hour += overflow;
  _time_stamp->minute %= Time::TimeData::SECOND_MINUTE_HOUR;
  HourElapsed->call(this, *_time_stamp);

  // Check for a new day, reset hours if so.
  if (_time_stamp->hour / Time::TimeData::HOUR_TO_DAY > 0)
  {
    _time_stamp->hour %= Time::TimeData::HOUR_TO_DAY;
    DayElapsed->call(this, *_time_stamp);
  }
}

/**
 * @return the mutable reference to this BaseClock's _time_stamp member
 *         for interrnal modification by derived types.
 */
Util::Memory::U_ptr<Time::TimeData>& Time::BaseClock::time_stamp_reference(void)
{
  return _time_stamp;
}