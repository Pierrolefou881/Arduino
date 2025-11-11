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
    virtual ~Stopwatch(void) = default;

    void tick(unsigned long tick_time_ms) override;
    virtual void start(void);
    void stop(void);
    virtual void reset(void);

    private:
      bool is_active{ };
  };
}