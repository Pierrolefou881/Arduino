#pragma once
#include "Speaker.hpp"

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

        static Util::Memory::S_ptr<InOut::Analog::AnalogInput> create_analog_input(int pin_number);
        static Util::Memory::S_ptr<InOut::Analog::PWMOutput> create_pwm_output(int pin_number);

        static Util::Memory::S_ptr<InOut::Sound::Speaker> create_speaker(
          int pin_number, int sound_duration = InOut::Sound::Speaker::DEFAULT_DURATION_MS);
    };
  }
}