#include "CapacitiveInput.hpp"
#include <Arduino.h>

const int InOut::Analog::CapacitiveInput::DEFAULT_SAMPLES{ 30 };
const int InOut::Analog::CapacitiveInput::DEFAULT_THRESHOLD{ 1000 };

/**
 * Intializes this CapacitiveInput with provided sender and receive pins and number
 * of samples required by call.
 * @param sender_pin connected to a 1MOhm resistor.
 * @param receive_pin connected to the other end of the resistor and the capacitive touch area.
 * @param samples per reading, defaulted to 30.
 * @param threshold necessary to consider this CapacitiveInput active, defaulted to 1000.
 */
InOut::Analog::CapacitiveInput::CapacitiveInput(int sender_pin, int receive_pin, int samples, int threshold)
  : InOut::InputBase{ InOut::InOutBase::NO_PIN_AFFECTED }
  , _sensor{ new CapacitiveSensor{ (uint8_t) sender_pin, (uint8_t) receive_pin } }
  , _samples{ samples }
  , _threshold{ threshold }
{
  // Empty body
}

/**
 * @return true if this CapacitiveInput is receiving a signal,
 *         false otherwise.
 */
bool InOut::Analog::CapacitiveInput::is_active(void) const
{
  return get_current_state() > _threshold;
}

/**
 * @return the raw value read by this CapacitiveInput.
 */
int InOut::Analog::CapacitiveInput::do_read_value(void)
{
  return _sensor->capacitiveSensor(_samples);
}