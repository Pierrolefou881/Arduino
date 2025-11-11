#include "DigitalOutput.hpp"
#include <Arduino.h>

/**
 * Initializes this DigitalOutput with the provided pin number.
 * @param pin_number must correspond to the physical ppin on the Arduino board.
 */
InOut::Digital::DigitalOutput::DigitalOutput(int pin_number) : InOut::OutputBase::OutputBase{ pin_number }
{
  // Empty body
}

/**
 * Writes down a value to the actuator connected at this DigitalOutput's _pin_number.
 * Value is clamped to either 0 or 1 (LOW or HIGH); if anything else is sent, HIGH
 * should replace the value.
 * @param value HIGH or LOW, if anything else is provided, HIGH should be sent instead.
 */
void InOut::Digital::DigitalOutput::write_value(int value)
{
  if (value != LOW && value != HIGH)
  {
    value = HIGH;
  }

  digitalWrite(get_pin_number(), value);
  set_current_state(value);
}

/**
 * Actuates this DigitalOutput.
 */
void InOut::Digital::DigitalOutput::turn_on(void)
{
  write_value(HIGH);
}

/**
 * Deactuates this DigitalOutput.
 */
void InOut::Digital::DigitalOutput::turn_off(void)
{
  write_value(LOW);
}

/**
 * Actuates or Deactuates this DigitalOutput,
 * depending on its current state.
 */
void InOut::Digital::DigitalOutput::toggle(void)
{
  switch (get_current_state()) {
  case HIGH:
    turn_off();
    break;
  case LOW: // Falls through, consider idle as the default state
  default:
    turn_on();
    break;
  }
}