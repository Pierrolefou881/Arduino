#pragma once
#include "Stopwatch.hpp"
#include <U_ptr.hpp>

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