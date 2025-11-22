#include "Arduino.h"
#include "DateDisplay.hpp"
#include <LiquidCrystal.h>
#include <Calendar.hpp>
#include <Thermometer.hpp>
#include <EventHandler.hpp>

const char* DigitalClock::Display::DateDisplay::DAY_NAMES[]{ "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim" };
const int DigitalClock::Display::DateDisplay::DISPLAY_ROW{ 0 };
const char DigitalClock::Display::DateDisplay::SEPARATOR{ '/' };
const int DigitalClock::Display::DateDisplay::DISPLAY_WIDTH{ 14 };

/**
 * Initializes this DateDisplay with provided screen and calendar.
 * Subscribes to calendar events and prints perpetual characters on the screen.
 * Subscribes also to the provided thermometer.
 * @param screen that shall do the display.
 * @param calendar back end logic for managing date.
 * @param screen_with for centering.
 */
DigitalClock::Display::DateDisplay::DateDisplay(const Util::Memory::S_ptr<LiquidCrystal>& screen,
                                                const Util::Memory::S_ptr<Time::Calendar>& calendar,
                                                int screen_width)
  : DigitalClock::Display::DisplayBase{ screen }
  , _calendar{ calendar }
  , _day_name_index{ (screen_width - DISPLAY_WIDTH) / 2 }
  , _day_number_index{ _day_name_index + 4 }
  , _month_index{ _day_number_index + 3 }
  , _year_index{ _month_index + 3}
{
  auto& the_screen = get_screen();
  the_screen->setCursor(_day_number_index + 2, DISPLAY_ROW);
  the_screen->write(SEPARATOR);
  
  _calendar->DayElapsed->add(this, &DigitalClock::Display::DateDisplay::on_day_elapsed);
  _calendar->MonthElapsed->add(this, &DigitalClock::Display::DateDisplay::on_month_elapsed);
  _calendar->YearElapsed->add(this, &DigitalClock::Display::DateDisplay::on_year_elapsed);

  // Force display
  on_year_elapsed(_calendar.get(), calendar->get_date_stamp());
}

DigitalClock::Display::DateDisplay::~DateDisplay(void)
{
  _calendar->YearElapsed->remove(this, &DigitalClock::Display::DateDisplay::on_year_elapsed);
  _calendar->MonthElapsed->remove(this, &DigitalClock::Display::DateDisplay::on_month_elapsed);
  _calendar->DayElapsed->remove(this, &DigitalClock::Display::DateDisplay::on_day_elapsed);
}

void DigitalClock::Display::DateDisplay::write(int desired_index, int value)
{
  auto& screen = get_screen();
  screen->setCursor(desired_index, DISPLAY_ROW);
  if (value < 10)
  {
    screen->write(' ');
    screen->setCursor(desired_index + 1, DISPLAY_ROW);
  }
  screen->print(value);
}

void DigitalClock::Display::DateDisplay::print_week_day(int week_day)
{
  auto& screen = get_screen();
  screen->setCursor(_day_name_index, DISPLAY_ROW);
  screen->print(DAY_NAMES[week_day]);
}

void DigitalClock::Display::DateDisplay::on_day_elapsed(const Time::Calendar* sender, const Time::DateData& args)
{
  print_week_day(args.week_day);
  write(_day_number_index, args.day);
}

void DigitalClock::Display::DateDisplay::on_month_elapsed(const Time::Calendar* sender, const Time::DateData& args)
{
  write(_month_index, args.month);
  on_day_elapsed(sender, args);
}

void DigitalClock::Display::DateDisplay::on_year_elapsed(const Time::Calendar* sender, const Time::DateData& args)
{
  write(_year_index, args.year);
  on_month_elapsed(sender, args);
}