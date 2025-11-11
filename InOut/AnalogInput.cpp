#include "AnalogInput.hpp"
#include <Arduino.h>

/**
 * Initializes this AnalogInput with the provided pin number.
 * @param pin_number must correspond to an analog input on the board.
 */
InOut::Analog::AnalogInput::AnalogInput(int pin_number) : InOut::InputBase::InputBase{ pin_number }
{
  // Empty Body
}

/**
 * @return always true, since AnalogInput should always be considered active.
 */
bool InOut::Analog::AnalogInput::is_active(void) const
{
  return true;
}

/**
 * @return the ADC value as read at this AnalogInput's _pin_number value.
 */
int InOut::Analog::AnalogInput::do_read_value(void)
{
  return analogRead(get_pin_number());
}