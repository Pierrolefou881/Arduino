#include "ColorSensor.hpp"
#include <InOutFactory.hpp>
#include <AnalogInput.hpp>
#include "ColorEncoder.hpp"

/**
 * Initializes this ColorSensor with the provided pin numbers for each
 * AnalogInput (one per color).
 * @param pin_red must correspond to the physical pin number connected to red color sensor.
 * @param pin_green must correspond to the physical pin number connected to green color sensor.
 * @param pin_blue must correspond to the physical pin number connected to blue color sensor.
 */
InOut::Color::ColorSensor::ColorSensor(int pin_red, int pin_green, int pin_blue) 
  : _red{ InOut::Factory::InOutFactory::create_analog_input(pin_red) }
  , _green{ InOut::Factory::InOutFactory::create_analog_input(pin_green) }
  , _blue { InOut::Factory::InOutFactory::create_analog_input(pin_blue) }
{
  // Empty body
}

/**
 * Encodes the color sensed by all three sensors on a RGB 32 bits unsigned integer.
 * Red ranges over bits 8-15, green over 16-23 and blue over 24-31. Bits 0-3 are left unused.
 * @return The color according to the following RGB pattern [00][red][green][blue]. If any of the
 *         sensor is null, return value should be zero.  
 */
unsigned long InOut::Color::ColorSensor::encode_color(void) const
{
  // Avoid null pointer errors
  if (_red == nullptr || _green == nullptr || _blue == nullptr)
  {
    return 0;
  }
  return Utils::Color::ColorEncoder::encode_color(
    _red->read_value() / 4, _green->read_value() / 4, _blue->read_value() / 4
  );
}