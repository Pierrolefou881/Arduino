#include "S_ptr.hpp"
#include "HardwareSerial.h"
#include "HourglassDisplay.hpp"
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
#include <ArrayList.hpp>
#include <LinkedList.hpp>
#include <LinkedListIterator.hpp>
#include <BaseClock.hpp>

#include <Arduino.h>

/**
 * Initializes this HourglassDisplay with the provided list of DigitalOutput instances
 * that should be connected to leds.
 * @param leds ensure item at index 0 is the second blinking led, then 1 for 10 minutes, 2 for 20...
 */
InOut::Digital::HourglassDisplay::HourglassDisplay(Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>* leds) 
  : OutputBase(NO_PIN_AFFECTED)
  , _leds{ new Util::Collection::ArrayList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ } }
  , _next_index{ 1 }
{
  Util::Collection::LinkedListIterator<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>> iterator{ leds };
  while (iterator.has_next())
  {
    _leds->append(iterator.get());
    iterator.next();
  }
}

/**
 * Translates tens of minutes into an ignited led.
 * @param value number of minutes, greater than 10.
 */
void InOut::Digital::HourglassDisplay::write_value(int value)
{
  auto index = value / 10;
  if (index == _next_index)
  {
    _next_index++;
  }
  for (auto i = 1; i <= index; i++)
  {
    _leds->at(index)->turn_on();
  }
}

/**
 * Resets this HourglassDisplay by turning off all leds.
 */
void InOut::Digital::HourglassDisplay::reset(void)
{
  for (auto i = 1; i < _leds->size(); i++)
  {
    _leds->at(i)->turn_off();
  }
  _next_index = 1;
}

/**
 * Updates the display at each minute.
 * @param sender unused.
 * @param args used for minutes.
 */
void InOut::Digital::HourglassDisplay::on_minute_elapsed(const Time::BaseClock *sender, const Time::TimeData& args)
{
  if (args.hour >= 1 || args.minute < 10)
  {
    return;
  }
  write_value(args.minute);
}

/**
 * Blinks the seconds led once every second.
 * @param sender unused.
 * @param args unused.
 */
void InOut::Digital::HourglassDisplay::on_second_elapsed(const Time::BaseClock *sender, const Time::TimeData& args)
{
  _leds->at(0)->toggle();
  if (_next_index < _leds->size())
  {
    _leds->at(_next_index)->toggle();
  }
}