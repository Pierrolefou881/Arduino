#pragma once
#include <stdint.h>
#include <S_ptr.hpp>
#include <AnalogInput.hpp>

namespace InOut
{
  namespace Color
  {
    /**
     * Encodes data gathered from 3 photo-transistors into
     * a RGB style color representation.
     */
    class ColorSensor
    {
      public:
        ColorSensor(int pin_red, int pin_green, int pin_blue);
        virtual ~ColorSensor(void) = default;

        unsigned long encode_color(void) const;

      private:
        Util::Memory::S_ptr<InOut::Analog::AnalogInput> _red{ };
        Util::Memory::S_ptr<InOut::Analog::AnalogInput> _green{ };
        Util::Memory::S_ptr<InOut::Analog::AnalogInput> _blue{ };
    };
  }
}