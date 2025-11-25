#pragma once
#include "Speaker.hpp"
#include "CapacitiveInput.hpp"

namespace Util
{
  namespace Memory
  {
    template<typename T>
    class S_ptr;
  }
}

namespace InOut
{
  namespace Digital
  {
    class DigitalOutput;
    class DigitalInput;
    class MemorySwitch;
    class CapacitiveDigitalInput;
  }

  namespace Analog
  {
    class AnalogInput;
    class PWMOutput;
  }
  
  namespace Factory
  {
    /**
     * Collection of InOut utility methods. Manages
     * pin assignation and memory allocation.
     */
    class InOutFactory
    {
      public:
        static Util::Memory::S_ptr<InOut::Digital::DigitalOutput> create_digital_output(int pin_number);
        static Util::Memory::S_ptr<InOut::Digital::DigitalInput> create_digital_input(int pin_number);
        static Util::Memory::S_ptr<InOut::Digital::MemorySwitch> create_memory_switch(int pin_number);
        static Util::Memory::S_ptr<InOut::Digital::CapacitiveDigitalInput> create_capacitive_digital_input(
          int sender_pin, int receive_pin, int samples = InOut::Analog::CapacitiveInput::DEFAULT_SAMPLES, 
          int threshold = InOut::Analog::CapacitiveInput::DEFAULT_THRESHOLD
        );

        static Util::Memory::S_ptr<InOut::Analog::AnalogInput> create_analog_input(int pin_number);
        static Util::Memory::S_ptr<InOut::Analog::PWMOutput> create_pwm_output(int pin_number);
        static Util::Memory::S_ptr<InOut::Analog::CapacitiveInput> create_capacitive_input(int sender_pin, int receive_pin, 
          int samples = InOut::Analog::CapacitiveInput::DEFAULT_SAMPLES, int threshold = InOut::Analog::CapacitiveInput::DEFAULT_THRESHOLD);

        static Util::Memory::S_ptr<InOut::Sound::Speaker> create_speaker(
          int pin_number, int sound_duration = InOut::Sound::Speaker::DEFAULT_DURATION_MS);
    };
  }
}