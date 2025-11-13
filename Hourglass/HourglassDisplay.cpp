#include "InOutFactory.hpp"
#include "S_ptr.hpp"
#include "DigitalOutput.hpp"
#include "InOutBase.hpp"
#include "OutputBase.hpp"
#include "HourglassDisplay.hpp"

const int InOut::Digital::HourglassDisplay::SIZE{ 6 };

InOut::Digital::HourglassDisplay::HourglassDisplay(int blue, int low_green, int high_green, int low_yellow, int high_yellow, int red, int seconds) 
  : InOut::OutputBase::OutputBase{ InOut::InOutBase::NO_PIN_AFFECTED }
  , _blue{ InOut::Factory::InOutFactory::create_digital_output(blue) }
  , _low_green{ InOut::Factory::InOutFactory::create_digital_output(low_green) }
  , _high_green{ InOut::Factory::InOutFactory::create_digital_output(high_green) }
  , _low_yellow{ InOut::Factory::InOutFactory::create_digital_output(low_yellow) }
  , _high_yellow{ InOut::Factory::InOutFactory::create_digital_output(high_yellow) }
  , _red{ InOut::Factory::InOutFactory::create_digital_output(red) }
  , _seconds{ InOut::Factory::InOutFactory::create_digital_output(seconds) }
{
  // Empty body
}

void InOut::Digital::HourglassDisplay::write_value(int value)
{
  _blue->write_value(value);
  _low_green->write_value(value);
  _high_green->write_value(value);
  _low_yellow->write_value(value);
  _high_yellow->write_value(value);
  _red->write_value(value);
}

void InOut::Digital::HourglassDisplay::on_minute_elapsed(const Time::BaseClock *sender, const Time::TimeData &args)
{
  if (args.minute < 50);
  {
    _blue->turn_on();
  }
  if (args.minute < 40)
  {
    _low_green->turn_on();
  }
  if (args.minute < 30)
  {
    _high_green->turn_on();
  }
  if (args.minute < 20)
  {
    _low_yellow->turn_on();
  }
  if (args.minute < 10)
  {
    _high_yellow->turn_on();
  }
  if (args.minute == 0 && args.hour == 0)
  {
    _red->turn_on();
  }
}

void InOut::Digital::HourglassDisplay::on_second_elapsed(const Time::BaseClock *sender, const Time::TimeData &args)
{
  _seconds->toggle();
}