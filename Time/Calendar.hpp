#pragma once
#include "BaseClock.hpp"
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <EventHandler.hpp>

namespace Time
{
  class BaseClock;
  struct TimeData;

  /**
   * Data object representing a date by its day,
   * month and year.
   */
  struct DateData
  {
    static const int MONTH_DURATIONS[];
    static const int DEFAULT_YEAR_DURATION;
    static const int WEEK_DURATION;
    static int find_week_day(DateData& date);
    static bool is_leap_year(int year);
    int week_day{ };
    int day{ };
    int month{ };
    int year{ };

    DateData(void);
    virtual ~DateData(void) = default;
  };

  /**
   * Automatic perpetual calendar that can
   * manage dates as DateData.
   */
  class Calendar
  {
  public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const Calendar, const DateData&>> DayElapsed{ new Util::Event::EventHandler<const Calendar, const DateData&>{ } };
    Util::Memory::U_ptr<Util::Event::EventHandler<const Calendar, const DateData&>> MonthElapsed{ new Util::Event::EventHandler<const Calendar, const DateData&>{ } };
    Util::Memory::U_ptr<Util::Event::EventHandler<const Calendar, const DateData&>> YearElapsed{ new Util::Event::EventHandler<const Calendar, const DateData&>{ } };

    Calendar(const Util::Memory::S_ptr<Time::BaseClock>& clock);
    virtual ~Calendar(void);

    const Time::DateData& get_date_stamp(void) const;
    void set_date_stamp(const Time::DateData& date_stamp);

  private:
    Util::Memory::S_ptr<Time::BaseClock> _clock{ };
    Util::Memory::U_ptr<Time::DateData> _date_stamp{ new Time::DateData{ } };

    void clock_day_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
    bool check_new_month(void) const;
  };
}