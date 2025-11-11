#pragma once

#include <S_ptr.hpp>
#include <PWMOutput.hpp>
#include <InOutFactory.hpp>

namespace InOut
{
  namespace Color
  {
    /**
     * Represents a RGB triple led to be used in conjunction with
     * ColorSensor. Color is encoded on a 32-bit integer as follows :
     * [0-7 empty][8-15 red][16-23 green][24-31 blue].
     */
    class RGBLight
    {
    public:
      RGBLight(int pin_red, int pin_green, int pin_blue);
      virtual ~RGBLight(void) = default;

      void display_color(unsigned long color) const;

    private:
      Util::Memory::S_ptr<InOut::Analog::PWMOutput> _red{ };
      Util::Memory::S_ptr<InOut::Analog::PWMOutput> _green{ };
      Util::Memory::S_ptr<InOut::Analog::PWMOutput> _blue{ };
    };
  }
}