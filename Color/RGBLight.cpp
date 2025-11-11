#include "RGBLight.hpp"
#include <InOutFactory.hpp>
#include <PWMOutput.hpp>
#include "ColorEncoder.hpp"

/**
 * Initializes this RGBLight with the provided pin numbers for each
 * PWM output (one per color).
 * @param pin_red must correspond to the physical pin number connected to red color PWM actuator.
 * @param pin_green must correspond to the physical pin number connected to green color PWM actuator.
 * @param pin_blue must correspond to the physical pin number connected to blue color PWM actuator.
 */
InOut::Color::RGBLight::RGBLight(int pin_red, int pin_green, int pin_blue) : _red{ InOut::Factory::InOutFactory::create_pwm_output(pin_red) }
  , _green{ InOut::Factory::InOutFactory::create_pwm_output(pin_green) }
  , _blue{ InOut::Factory::InOutFactory::create_pwm_output(pin_blue) }
{
  // Empty body
}

/**
 * Decodes the provided RGB color code and sends the appropriate PWM signal
 * to each respective LED. If any actuator is null, does nothing. Color is
 * encoded on a 32-bit unsigned integer as follows : 
 * [0-7 empty][8-15 red][16-23 green][24-31 blue]
 */
void InOut::Color::RGBLight::display_color(unsigned long color) const
{
  // Error case, do nothing if either actuator is null
  if (_red == nullptr || _green == nullptr || _blue == nullptr)
  {
    return;
  }

  _red->write_value(Utils::Color::ColorEncoder::decode_red(color));
  _green->write_value(Utils::Color::ColorEncoder::decode_green(color));
  _blue->write_value(Utils::Color::ColorEncoder::decode_blue(color));
}