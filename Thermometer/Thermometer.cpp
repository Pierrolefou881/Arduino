#include "Thermometer.hpp"
#include <InOutFactory.hpp>

const float Sensor::Thermometer::VOLTAGE_COEFFICIENT = 5.0f;
const float Sensor::Thermometer::ADC_COEFFICIENT = 1024.0f;
const float Sensor::Thermometer::CELSIUS_COEFFICIENT = 100.0f;
const float Sensor::Thermometer::CELSIUS_CONSTANT = .5f;
const float Sensor::Thermometer::FARENHEIT_COEFFICIENT = 1.8f;
const float Sensor::Thermometer::FARENHEIT_CONSTANT = 32.0f;
const float Sensor::Thermometer::KELVIN_CONSTANT = 273.15;

/**
 * Initializes this Thermometer with the assigned pin number.
 * @param pin_number connected to this Thermometer's sensor.
 */
Sensor::Thermometer::Thermometer(int pin_number)
{
  _sensor = InOut::Factory::InOutFactory::create_analog_input(pin_number);
}

/**
 * @return the temperature read by this Thermometer, in °C.
 */
float Sensor::Thermometer::read_celsius(void) const
{
  return (read_voltage() - CELSIUS_CONSTANT) * CELSIUS_COEFFICIENT;
}

/**
 * @return the temerature read by this Thermometer, in °F.
 */
float Sensor::Thermometer::read_farenheit(void) const
{
  return (read_celsius() * FARENHEIT_COEFFICIENT) + FARENHEIT_CONSTANT;
}

/**
 * @return the temperature read by this Thermometer, in K.
 */
float Sensor::Thermometer::read_kelvin(void) const
{
  return read_celsius() + KELVIN_CONSTANT;
}

float Sensor::Thermometer::read_voltage(void) const
{
  return _sensor != nullptr ? (_sensor->read_value() / ADC_COEFFICIENT) * VOLTAGE_COEFFICIENT : NAN;
}