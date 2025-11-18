#include "Timer.hpp"

/**
 * Resets _time_stamp to the timer settings.
 */
void Time::Timer::reset(void)
{
  set_time_stamp(*_timer_setting);
  OnReset->call(this, get_time_stamp());
}

/**
 * Replaces the _time_stamp member's value with the provided one.
 * @param time_stamp new timer value to count down.
 */
void Time::Timer::set_time_stamp(const Time::TimeData& time_stamp)
{
  Time::Stopwatch::set_time_stamp(time_stamp);
  _timer_setting = new Time::TimeData{ time_stamp };
}

/**
 * Updates the _time_stamp in reverse.
 * @param tick_duration_ms time elapsed since last call in milliseconds.
 */
void Time::Timer::update_time_stamp(unsigned long tick_duration_ms)
{
  if (!is_running())
  {
    return;
  }

  if ((unsigned long) time_stamp_reference()->millisecond >= tick_duration_ms || drain_millis_from_seconds())
  {
    time_stamp_reference()->millisecond -= tick_duration_ms;
  }
  else 
  {
    time_stamp_reference()->millisecond = 0;
    SecondElapsed->call(this, get_time_stamp());
    stop();
    CountdownComplete->call(this, nullptr);
  }
}

bool Time::Timer::drain_millis_from_seconds(void)
{
  if (time_stamp_reference()->second > 0 || drain_seconds_from_minutes())
  {
    time_stamp_reference()->second--;
    time_stamp_reference()->millisecond += Time::TimeData::MILLISECOND_TO_SECOND;
    SecondElapsed->call(this, get_time_stamp());
    return true;
  }
  return false;
}

bool Time::Timer::drain_seconds_from_minutes(void)
{
  if (time_stamp_reference()->minute > 0 || drain_minutes_from_hours())
  {
    time_stamp_reference()->minute--;
    time_stamp_reference()->second += Time::TimeData::SECOND_MINUTE_HOUR;
    MinuteElapsed->call(this, get_time_stamp());
    return true;
  }
  return false;
}

bool Time::Timer::drain_minutes_from_hours(void)
{
  auto has_hours = time_stamp_reference()->hour > 0;
  if (has_hours)
  {
    time_stamp_reference()->hour--;
    time_stamp_reference()->minute += Time::TimeData::SECOND_MINUTE_HOUR;
    HourElapsed->call(this, get_time_stamp());
  }
  return has_hours;
}