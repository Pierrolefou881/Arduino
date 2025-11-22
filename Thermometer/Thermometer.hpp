#pragma once
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <AnalogInput.hpp>

namespace Util
{
  namespace Event
  {
    template<typename TS, typename TA>
    class EventHandler;
  }
}

namespace Sensor
{
  /**
   * Holds the value of a temperature in the
   * three main units: celsius, farenheit and kelvin.
   */
  struct TemperatureData
  {
    static const float FARENHEIT_COEFFICIENT;
    static const float FARENHEIT_CONSTANT;
    static const float KELVIN_CONSTANT;

    static float celsius_to_farenheit(float temperature_c);
    static float celsius_to_kelvin(float temperature_c);

    float celsius{ };
    float farenheit{ };
    float kelvin{ };

    /**
     * Initializes this TemperatureData with the provided temperature in all
     * three units.
     * @param c in celsius.
     * @param f in farenheit.
     * @param k in kelvin.
     */
    TemperatureData(float c, float f, float k) : celsius{ c }, farenheit{ f }, kelvin{ k }
    {
      // Empty body
    }
  };

  /**
   * Converts ADC data from analog pin to voltage and
   * temperatures, expressed in Celsius, Farenheit or Kelvin.
   */
  class Thermometer
  {
  public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const Thermometer, const TemperatureData&>> TemperatureChanged{ };

    Thermometer(int pin_number);
    virtual ~Thermometer(void);

    int update(void) const;

    float read_celsius(void) const;
    float read_farenheit(void) const;
    float read_kelvin(void) const;

  private:
    static const float VOLTAGE_COEFFICIENT;
    static const float ADC_COEFFICIENT;
    static const float CELSIUS_COEFFICIENT;
    static const float CELSIUS_CONSTANT;

    static float adc_to_voltage(int adc_reading);
    static float voltage_to_celsius(float voltage);
    
    Util::Memory::S_ptr<InOut::Analog::AnalogInput> _sensor{ };
    
    float read_voltage(void) const;
    void on_sensor_reading_changed(const InOut::InOutBase* sender, int args);
  };
}