#include "Calendar.hpp"

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
 * Duration of a week, expressed in days.
 */
const int Time::DateData::WEEK_DURATION{ 7 };

/**
 * Finds and assigns to the given date the correct day of the week.
 * @param date non const, shall be modified to bear new data on day of
 *             the week.
 * @return the day of the week as an int between 0 and 7;
 */
int Time::DateData::find_week_day(DateData& date)
{
  // Reset
  DateData reference{ };
  date.week_day = 0;
  int days_elapsed{ 0 };

  for (; reference.year < date.year; reference.year++)
  {
    days_elapsed += is_leap_year(reference.year) ? DEFAULT_YEAR_DURATION + 1 : DEFAULT_YEAR_DURATION;
  }
  for (; reference.month < date.month; reference.month++)
  {
    days_elapsed += reference.month == 2 && is_leap_year(date.year) ? MONTH_DURATIONS[reference.month] + 1 : MONTH_DURATIONS[reference.month];
  }
  
  days_elapsed += date.day - reference.day;
  date.week_day = (days_elapsed + reference.week_day) % 7;
  return date.week_day;
}

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
* Initializes a default DateData on Jan 1st, 2020. This
* is an arbitrarily chosen default date.
* reminder: Jan 1st, 2020 was a wednesday.
*/
Time::DateData::DateData(void) : day{ 1 }, month{ 1 }, year{ 2020 }, week_day{ 2 }
{
// Empty body
}

/**
 * Initializes this Calendar with the provided BaseClock and subscribes it to
 * its DayElapsed event to sync with it.
 * @param clock should not be of any derived type of BaseClock (although it might work with Stopwatch).
 */
Time::Calendar::Calendar(const Util::Memory::S_ptr<Time::BaseClock>& clock) : _clock{ clock }
{
  _clock->DayElapsed->add(this, &Time::Calendar::clock_day_elapsed);
}

Time::Calendar::~Calendar(void)
{
  _clock->DayElapsed->remove(this, &Time::Calendar::clock_day_elapsed);
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
  Time::DateData::find_week_day(*_date_stamp);
}

void Time::Calendar::clock_day_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  _date_stamp->day += 1;
  _date_stamp->week_day += 1;
  _date_stamp->week_day %= Time::DateData::WEEK_DURATION;
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