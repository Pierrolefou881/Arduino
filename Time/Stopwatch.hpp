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