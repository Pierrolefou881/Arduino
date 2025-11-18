#pragma once
#include "Stopwatch.hpp"

namespace Time 
{
  /**
   * Countdown timer; basically a reverse
   * Stopwatch that stops when it reaches
   * 00:00:00:000.
   */
  class Timer : public Stopwatch
  {
  public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const Timer, void*>> CountdownComplete{ new Util::Event::EventHandler<const Timer, void*> };

    virtual ~Timer(void) = default;

    void reset(void) override;
    void set_time_stamp(const Time::TimeData& time_stamp) override;

  protected:
    void update_time_stamp(unsigned long tick_duration_ms) override;

  private:
    Util::Memory::U_ptr<TimeData> _timer_setting{ };

    bool drain_millis_from_seconds(void);
    bool drain_seconds_from_minutes(void);
    bool drain_minutes_from_hours(void);
  };
}