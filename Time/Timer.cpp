#include "Timer.hpp"

/**
 * Keeps a reference to timer setting before starting the countdown.
 */
void Time::Timer::start(void)
{
  // CAUTION: Make a copy, don't change ownership.
  _timer_setting = time_stamp_reference().get();
  Time::Stopwatch::start();
}

/**
 * Resets _time_stamp to the timer settings.
 */
void Time::Timer::reset(void)
{
  time_stamp_reference() = _timer_setting.get();
}

/**
 * Updates the _time_stamp in reverse.
 * @param tick_duration_ms time elapsed since last call in milliseconds.
 */
void Time::Timer::update_time_stamp(unsigned long tick_duration_ms)
{
  if (time_stamp_reference()->millisecond >= tick_duration_ms || drain_millis_from_seconds())
  {
    time_stamp_reference()->millisecond -= tick_duration_ms;
  }
  else 
  {
    time_stamp_reference()->millisecond = 0;
    on_second_elapsed();
    on_countdown_complete();
  }
}

void Time::Timer::on_countdown_complete(void) const
{
  stop();
  if (CountdownComplete)
  {
    CountdownComplete->call(this, nullptr);
  }
}

bool Time::Timer::drain_millis_from_seconds(void) const
{
  if (time_stamp_reference()->second > 0 || drain_seconds_from_minutes())
  {
    time_stamp_reference()->second--;
    time_stamp_reference()->millisecond += Time::TimeData::MILLISECOND_TO_SECOND;
    on_second_elapsed();
    return true;
  }
  return false;
}

bool Time::Timer::drain_seconds_from_minutes(void) const
{
  if (time_stamp_reference()->minute > 0 || drain_minutes_from_hours())
  {
    time_stamp_reference()->minute--;
    time_stamp_reference()->second += Time::TimeData::SECOND_MINUTE_HOUR;
    on_minute_elapsed();
    return true;
  }
  return false;
}

bool Time::Timer::drain_minutes_from_hours(void) const
{
  auto has_hours = time_stamp_reference()->hour > 0;
  if (has_hours)
  {
    time_stamp_reference()->hour--;
    time_stamp_reference()->minute += Time::TimeData::SECOND_MINUTE_HOUR;
    on_hour_elapsed();
  }
  return has_hours;
}