#include "PWMOutput.hpp"
#include <Arduino.h>

/**
 * Initializes this PWMOutput with the provided pin number.
 * @param pin_number must correspond to a physical PWM pin on the board.
 */
InOut::Analog::PWMOutput:: PWMOutput(int pin_number) : InOut::OutputBase::OutputBase{ pin_number }
{
  // Empty body
}

/**
 * Writes down a value on the actuator located at _pin_number on the board.
 * If value is negative, it shall be changed to 0. Likewise, it shall be
 * changed to 255 if it exceeds this value.
 * @param value must be between 0 and 255.
 */
void InOut::Analog::PWMOutput::write_value(int value)
{
  // Clamp value in an unsigned byte
  if (value < 0)
  {
    value = 0;
  }
  else if (value > 255)
  {
    value = 255;
  }

  analogWrite(get_pin_number(), value);
  set_current_state(value);
}

/**
 * Shuts down the actuator located at _pin_number;
 */
void InOut::Analog::PWMOutput::shutdown(void)
{
  write_value(0);
}