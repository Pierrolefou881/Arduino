#pragma once

#include <S_ptr.hpp>
#include <AnalogInput.hpp>
#include <Math.h>

namespace Sensor
{
  /**
   * Converts ADC data from analog pin to voltage and
   * temperatures, expressed in Celsius, Farenheit or Kelvin.
   */
  class Thermometer
  {
    public:
    Thermometer(int pin_number);
    virtual ~Thermometer(void) = default;

    float read_celsius(void) const;
    float read_farenheit(void) const;
    float read_kelvin(void) const;

    private:
    float read_voltage(void) const;

    Util::Memory::S_ptr<InOut::Analog::AnalogInput> _sensor{ };

    static const float VOLTAGE_COEFFICIENT;
    static const float ADC_COEFFICIENT;
    static const float CELSIUS_COEFFICIENT;
    static const float CELSIUS_CONSTANT;
    static const float FARENHEIT_COEFFICIENT;
    static const float FARENHEIT_CONSTANT;
    static const float KELVIN_CONSTANT;
  };
}