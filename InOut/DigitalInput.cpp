#include "DigitalInput.hpp"
#include <Arduino.h>

/**
 * Initializes this DigitalInput with the provided pin number.
 * @param pin_number should correspond with a digital or PWM pin on the board.
 */
InOut::Digital::DigitalInput::DigitalInput(int pin_number) : InOut::InputBase::InputBase{ pin_number }
{
  // Empty body
}

/**
 * @return LOW or HIGH (0 or 1), depending on the sensor's state at this
 * DigitalInput's _pin_number value.
 */
int InOut::Digital::DigitalInput::do_read_value(void)
{
  return digitalRead(get_pin_number());
}

/**
 * @return true if this DigitalInput's _current_state is HIGH,
 *         false otherwise.
 */
bool InOut::Digital::DigitalInput::is_active(void) const
{
  return get_current_state() == HIGH;
}