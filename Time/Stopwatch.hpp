#pragma once
#include "BaseClock.hpp"

namespace Time
{
  /**
   * Clock that can be started, stopped and set back to
   * zero.
   */
  class Stopwatch : public BaseClock
  {
    public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const Time::TimeData&>> OnStart{ new Util::Event::EventHandler<const BaseClock, const Time::TimeData&>{ } };
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const Time::TimeData&>> OnStop{ new Util::Event::EventHandler<const BaseClock, const Time::TimeData&>{ } };
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const Time::TimeData&>> OnReset{ new Util::Event::EventHandler<const BaseClock, const Time::TimeData&>{ } };

    virtual ~Stopwatch(void) = default;

    virtual void start(void);
    void stop(void);
    virtual void reset(void);

    bool is_running(void) const;

  protected:
    void update_time_stamp(unsigned long tick_duration_ms) override;

    private:
      bool is_active{ };
  };
}