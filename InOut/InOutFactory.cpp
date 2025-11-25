#include "InOutFactory.hpp"
#include <Arduino.h>
#include <S_ptr.hpp>
#include "DigitalOutput.hpp"
#include "DigitalInput.hpp"
#include "AnalogInput.hpp"
#include "PWMOutput.hpp"
#include "Speaker.hpp"
#include "MemorySwitch.hpp"
#include "CapacitiveDigitalInput.hpp"

using namespace InOut;

/**
 * Assigns digital output at the given pin number and creates a corresponding
 * instance of DigitalOutput.
 * @param pin_number must correspond to a physical pin connected to a digital actuator.
 * @return a pointer to the newly created DigitalOutput.
 */
Util::Memory::S_ptr<Digital::DigitalOutput> Factory::InOutFactory::create_digital_output(int pin_number)
{
  pinMode(pin_number, OUTPUT);
  return { new Digital::DigitalOutput{ pin_number} };
}

/**
 * Assigns digital input at the given pin number and creates a corresponding
 * instance of DigitalInput.
 * @param pin_number must correspond to a physical pin connected to a digital sensor.
 * @return a pointer to the newly created DigitalInput.
 */
Util::Memory::S_ptr<Digital::DigitalInput> Factory::InOutFactory::create_digital_input(int pin_number)
{
  pinMode(pin_number, INPUT);
  return { new Digital::DigitalInput{ pin_number} };
}

/**
 * Assigns digital input at the given pin number and creates a corresponding
 * instance of MemorySwitch decorator.
 * @param pin_number must correspond to a physical pin connected to a digital sensor.
 * @return a pointer to the newly created MemorySwitch decorator.
 */
Util::Memory::S_ptr<Digital::MemorySwitch> Factory::InOutFactory::create_memory_switch(int pin_number)
{
  auto input = create_digital_input(pin_number);
  return { new Digital::MemorySwitch{ input } };
}

/**
 * Creates a CapacitiveDigitalInput wrapper facade for the Arduino Starter pack CapacitiveSensor class.
 * @param sender_pin connected to a 1MOhm resistor.
 * @param receive_pin connected to the other end of the resistor and the capacitive touch area.
 * @param samples per call of the sensor, defaulted to 30.
 * @param threshold to consider the sensor active, defaulted to 1000.
 * @return a pointer to a newly created CapacitiveDigitalInput instance connected to the provided pins.
 * @see InOut::Analog::CapacitiveInput
 */
Util::Memory::S_ptr<Digital::CapacitiveDigitalInput> Factory::InOutFactory::create_capacitive_digital_input(int sender_pin, int receive_pin, int samples, int threshold)
{
  auto analog = create_capacitive_input(sender_pin, receive_pin, samples, threshold);
  return { new InOut::Digital::CapacitiveDigitalInput{ analog } };
}

/**
 * @param pin_number must correspond to a physical pin connected to a analog sensor.
 * @return a pointer to a newly created AnalogInput instance referring to pin number.
 */
Util::Memory::S_ptr<Analog::AnalogInput> Factory::InOutFactory::create_analog_input(int pin_number)
{
  return { new Analog::AnalogInput{pin_number} };
}

/**
 * @param pin_number must correspond to a physical pin connected to a PWM actuator.
 * @return a pointer to a newly created PWMOutput instance referring to pin number.
 */
Util::Memory::S_ptr<Analog::PWMOutput> Factory::InOutFactory::create_pwm_output(int pin_number)
{
  pinMode(pin_number, OUTPUT);
  return { new Analog::PWMOutput{ pin_number } };
}

/**
 * Creates a CapacitiveInput wrapper facade for the Arduino Starter pack CapacitiveSensor class.
 * @param sender_pin connected to a 1MOhm resistor.
 * @param receive_pin connected to the other end of the resistor and the capacitive touch area.
 * @param samples per call of the sensor, defaulted to 30.
 * @param threshold to consider the sensor active, defaulted to 1000.
 * @return a pointer to a newly created CapacitiveInput instance connected to the provided pins.
 */
Util::Memory::S_ptr<Analog::CapacitiveInput> Factory::InOutFactory::create_capacitive_input(int sender_pin, int receive_pin, int samples, int threshold)
{
  return { new Analog::CapacitiveInput{ sender_pin, receive_pin, samples, threshold } };
}

/**
 * @param pin_number must correspond to a physical pin connected to a speaker system.
 * @param sound_duration in mS of each sound emitted. If not provided, default value assigned.
 * @return a pointer to a newly created Speaker instance referring to pin number.
 */
Util::Memory::S_ptr<Sound::Speaker> Factory::InOutFactory::create_speaker(int pin_number, int sound_duration)
{
  pinMode(pin_number, OUTPUT);
  return { new Sound::Speaker{ pin_number, sound_duration } };
}