#include "Calendar.hpp"
#include "BaseClock.hpp"

/**
 * All the month durations in days. Each month is represented at the corresponding
 * index for trasparency and ease of use. 0 left default, since it shall not be used.
 */
const int Time::DateData::MONTH_DURATIONS[]{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/**
 * Default duration of a standard, non-leap, year, expressed in days.
 */
const int Time::DateData::DEFAULT_YEAR_DURATION{ 365 };

/**
 * Reminder: A leap year is a multiple of 4 but not 100 or a multiple of 400;
 * @param year to test.
 * @return true if year is a leap year, false otherwise.
 */
bool Time::DateData::is_leap_year(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
 * Assigns a new BaseClock to this Calendar and subscribes to its DayElapsed event
 * to keep this Calendar up to date (pun intended).
 */
void Time::Calendar::assign_clock(const Util::Memory::S_ptr<Time::BaseClock>& clock)
{
  Time::Calendar* non_const = this;
  if (_clock != nullptr && _clock != clock)
  {
    _clock->DayElapsed->remove(non_const, &Time::Calendar::clock_day_elapsed);
  }
  _clock = clock;
  clock->DayElapsed->add(non_const, &Time::Calendar::clock_day_elapsed);
}

/**
 * @return the reference to this Calendar's date stamp.
 */
const Time::DateData& Time::Calendar::get_date_stamp(void) const
{
  return *_date_stamp;
}

/**
 * Assigns a new date stamp to this Calendar.
 * @param date_stamp the new date to assign.
 */
void Time::Calendar::set_date_stamp(const Time::DateData& date_stamp)
{
  _date_stamp = new DateData{ date_stamp };
}

void Time::Calendar::clock_day_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  _date_stamp->day += 1;
  DayElapsed->call(this, *_date_stamp);

  // Check for new month. If not, just leave here;
  if (!check_new_month())
  {
    return;
  }

  _date_stamp->month += 1;
  _date_stamp->day = 1;     // Avoid modulos, all months start at 1.
  MonthElapsed->call(this, *_date_stamp);

  if (_date_stamp->month > 12)
  {
    _date_stamp->year += 1;
    _date_stamp->month = 1;
    YearElapsed->call(this, *_date_stamp);
  }
}

bool Time::Calendar::check_new_month(void) const
{
  return _date_stamp->day > Time::DateData::MONTH_DURATIONS[_date_stamp->month]
      && (_date_stamp->month != 2                                                       // Nominal Case
      || !Time::DateData::is_leap_year(_date_stamp->year)                               // February case - normal year
      || _date_stamp->day > Time::DateData::MONTH_DURATIONS[_date_stamp->month] + 1);   // February case - leap year
}