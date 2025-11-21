#include "TimeDisplay.hpp"
#include <LiquidCrystal.h>
#include <BaseClock.hpp>
#include <EventHandler.hpp>

const int DigitalClock::Display::TimeDisplay::DISPLAY_WIDTH{ 8 };
const int DigitalClock::Display::TimeDisplay::DISPLAY_ROW{ 1 };
const char DigitalClock::Display::TimeDisplay::SEPARATOR{ ':' };

/**
 * Initializes this TimeDisplay with the provided LiquidCrystal reference and BaseClock.
 * Subscribes to the clock's events.
 * Puts in place the default separators, since they shall never be changed.
 * @param screen in charge of the display of the time, shall not be null.
 * @param clock to subscribe to, shall no be null.
 * @param screen_width in columns. Defaulted at 16. Must be at least 8.
 */
DigitalClock::Display::TimeDisplay::TimeDisplay(const Util::Memory::S_ptr<LiquidCrystal>& screen,
                                                const Util::Memory::S_ptr<Time::BaseClock>& clock, 
                                                int screen_width)
  : DigitalClock::Display::TimeDisplay::DisplayBase(screen)
  , _clock{ clock }
  , _hour_index{ (screen_width - DISPLAY_WIDTH) / 2 }
  , _minute_index{ _hour_index + 3 }
  , _second_index{ _minute_index + 3 }
{
  auto& the_screen = get_screen();
  the_screen->clear();
  the_screen->setCursor(_hour_index + 2, DISPLAY_ROW);
  the_screen->write(SEPARATOR);
  the_screen->setCursor(_minute_index + 2, DISPLAY_ROW);
  the_screen->write(SEPARATOR);

  _clock->SecondElapsed->add(this, &DigitalClock::Display::TimeDisplay::on_second_elapsed);
  _clock->MinuteElapsed->add(this, &DigitalClock::Display::TimeDisplay::on_minute_elapsed);
  _clock->HourElapsed->add(this, &DigitalClock::Display::TimeDisplay::on_hour_elapsed);

  // Force update on the screen
  auto time_stamp = _clock->get_time_stamp();
  auto clk_ptr = _clock.get();
  on_hour_elapsed(clk_ptr, time_stamp);
  on_minute_elapsed(clk_ptr, time_stamp);
  on_second_elapsed(clk_ptr, time_stamp);
}

DigitalClock::Display::TimeDisplay::~TimeDisplay(void)
{
  _clock->HourElapsed->remove(this, &DigitalClock::Display::TimeDisplay::on_hour_elapsed);
  _clock->MinuteElapsed->remove(this, &DigitalClock::Display::TimeDisplay::on_minute_elapsed);
  _clock->SecondElapsed->remove(this, &DigitalClock::Display::TimeDisplay::on_second_elapsed);
}

/**
 * Does nothing. Data update is done through events.
 */
void DigitalClock::Display::TimeDisplay::update(void)
{
  // Empty body
}

/**
 * Refreshes the display of the seconds segment.
 * @param sender must be the same as _clock member and not null.
 * @param args time to display.
 */
void DigitalClock::Display::TimeDisplay::on_second_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  write(_second_index, args.second);  
}

/**
 * Refreshes the display of the minutes segment.
 * @param sender must be the same as _clock member and not null.
 * @param args time to display.
 */
void DigitalClock::Display::TimeDisplay::on_minute_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  write(_minute_index, args.minute);
}

/**
 * Refreshes the display of the hours segment.
 * @param sender must be the same as _clock member and not null.
 * @param args time to display.
 */
void DigitalClock::Display::TimeDisplay::on_hour_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  write(_hour_index, args.hour);
}

void DigitalClock::Display::TimeDisplay::write(int desired_index, int value)
{
  auto& screen = get_screen();
  screen->setCursor(desired_index, DISPLAY_ROW);
  if (value < 10)
  {
    screen->write('0');
    screen->setCursor(desired_index + 1, DISPLAY_ROW);
  }
  screen->print(value);
}