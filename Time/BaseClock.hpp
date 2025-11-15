#pragma once
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Callback.hpp>
#include <EventHandler.hpp>

namespace Time
{
  /**
   * Holds time values from milliseconds up to hours.
   */
  struct TimeData
  {
    static const int MILLISECOND_TO_SECOND;
    static const int SECOND_MINUTE_HOUR;
    static const int HOUR_TO_DAY;

    int hour{ };
    int minute{ };
    int second{ };
    int millisecond{ };
  };

  /**
   * Basic clock functionnalities. Gives hour, minute,
   * second and millisecond. Runs continuously but can
   * be set at any time.
   */
  class BaseClock
  {
  public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const TimeData&>> SecondElapsed{ new Util::Event::EventHandler<const BaseClock, const TimeData&> };
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const TimeData&>> MinuteElapsed{ new Util::Event::EventHandler<const BaseClock, const TimeData&> };
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const TimeData&>> HourElapsed{ new Util::Event::EventHandler<const BaseClock, const TimeData&> };
    Util::Memory::U_ptr<Util::Event::EventHandler<const BaseClock, const TimeData&>> DayElapsed{ new Util::Event::EventHandler<const BaseClock, const TimeData&> };

    virtual ~BaseClock(void) = default;
    virtual void tick(unsigned long tick_time_ms);
    const TimeData& get_time_stamp(void) const;
    void set_time_stamp(const TimeData& time_stamp);

   protected:
    virtual void update_time_stamp(unsigned long tick_duration_ms);
    Util::Memory::U_ptr<TimeData>& time_stamp_reference(void);

    void on_second_elapsed(void) const;
    void on_minute_elapsed(void) const;
    void on_hour_elapsed(void) const;
    void on_day_elapsed(void) const;

  private:
    Util::Memory::U_ptr<TimeData> _time_stamp{ new TimeData{ } };
    unsigned long _last_tick{ };
  };
}