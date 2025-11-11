#include "Callback.hpp"
#include "S_ptr.hpp"
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
    Util::Memory::S_ptr<Util::Event::Callback<const Timer, void*>> CountdownComplete{ };

    virtual ~Timer(void) = default;

    void start(void) override;
    void reset(void) override;

  protected:
    void update_time_stamp(unsigned long tick_duration_ms) override;

  private:
    Util::Memory::U_ptr<TimeData> _timer_setting{ };
    
    void on_countdown_complete(void) const;

    bool drain_millis_from_seconds(void) const;
    bool drain_seconds_from_minutes(void) const;
    bool drain_minutes_from_hours(void) const;
  };
}