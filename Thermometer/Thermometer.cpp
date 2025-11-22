#include "Thermometer.hpp"
#include <InOutBase.hpp>
#include <InOutFactory.hpp>
#include <EventHandler.hpp>
#include <math.h>

/**
 * Coefficient used in temperature conversions from celsius to
 * farenheit (and reversely).
 * Reminder: F = 1.8 * C + 32.
 */
const float Sensor::TemperatureData::FARENHEIT_COEFFICIENT = 1.8f;

/**
 * Constant used in temperature conversions from Celsius to
 * Farenheit (and reversely).
 * Reminder: F = 1.8 * C + 32.
 */
const float Sensor::TemperatureData::FARENHEIT_CONSTANT = 32.0f;

/**
 * Constant used to convert a temcperature in Celsius to Kelvin.
 * Reminder: K = C + 273.15.
 */
const float Sensor::TemperatureData::KELVIN_CONSTANT = 273.15f;

/**
 * Converts a temperature from Celsius to Farenheit.
 * @param temperature_c to convert, in Celsius.
 * @return the Farenheit conversion of temperature_c.
 */
float Sensor::TemperatureData::celsius_to_farenheit(float temperature_c)
{
  return (temperature_c * FARENHEIT_COEFFICIENT) + FARENHEIT_CONSTANT;
}

/**
 * Converts a temperature from Celsius to Kelvin.
 * @param temperature_c to convert, in Celsius.
 * @return the Kelvin conversion of temperature_c.
 */
float Sensor::TemperatureData::celsius_to_kelvin(float temperature_c)
{
  return temperature_c + KELVIN_CONSTANT;
}

const float Sensor::Thermometer::VOLTAGE_COEFFICIENT = 5.0f;
const float Sensor::Thermometer::ADC_COEFFICIENT = 1024.0f;
const float Sensor::Thermometer::CELSIUS_COEFFICIENT = 100.0f;
const float Sensor::Thermometer::CELSIUS_CONSTANT = .5f;

float Sensor::Thermometer::adc_to_voltage(int adc_reading)
{
  return (adc_reading / ADC_COEFFICIENT) * VOLTAGE_COEFFICIENT;
}

float Sensor::Thermometer::voltage_to_celsius(float voltage)
{
  return (voltage - CELSIUS_CONSTANT) * CELSIUS_COEFFICIENT;
}

/**
 * Initializes this Thermometer with the assigned pin number. Subscribes to the sensor's
 * StateChanged event.
 * @param pin_number connected to this Thermometer's sensor.
 */
Sensor::Thermometer::Thermometer(int pin_number)
  : TemperatureChanged{ new Util::Event::EventHandler<const Sensor::Thermometer, const Sensor::TemperatureData&>{ } }
  , _sensor{ InOut::Factory::InOutFactory::create_analog_input(pin_number) }
{
  _sensor->StateChanged->add(this, &Sensor::Thermometer::on_sensor_reading_changed);
}

Sensor::Thermometer::~Thermometer(void)
{
  _sensor->StateChanged->remove(this, &Sensor::Thermometer::on_sensor_reading_changed);
}

/**
 * Calls the read_value method on the sensor. Base call for every direct temperature
 * reading or for triggering the TemperatureChanged event.
 * @return the raw reading on the sensor.
 */
int Sensor::Thermometer::update(void) const
{
  return _sensor->read_value();
}

/**
 * @return the temperature read by this Thermometer, in °C.
 */
float Sensor::Thermometer::read_celsius(void) const
{
  return voltage_to_celsius(read_voltage());
}

/**
 * @return the temerature read by this Thermometer, in °F.
 */
float Sensor::Thermometer::read_farenheit(void) const
{
  return Sensor::TemperatureData::celsius_to_farenheit(read_celsius());
}

/**
 * @return the temperature read by this Thermometer, in K.
 */
float Sensor::Thermometer::read_kelvin(void) const
{
  return Sensor::TemperatureData::celsius_to_kelvin(read_celsius());
}

float Sensor::Thermometer::read_voltage(void) const
{
  return _sensor != nullptr ? adc_to_voltage(update()) : NAN;
}

void Sensor::Thermometer::on_sensor_reading_changed(const InOut::InOutBase* sender, int args)
{
  auto voltage = adc_to_voltage(args);
  auto celsius = voltage_to_celsius(voltage);
  Sensor::TemperatureData td
  {
    celsius,
    Sensor::TemperatureData::celsius_to_farenheit(celsius),
    Sensor::TemperatureData::celsius_to_kelvin(celsius),
  };
  TemperatureChanged->call(this, td);
}