#pragma once

#include <S_ptr.hpp>

class LiquidCrystal;

namespace DigitalClock
{
  namespace Display
  {
    class DisplayBase
    {
    public:
      DisplayBase(const Util::Memory::S_ptr<LiquidCrystal>& screen);
      virtual ~DisplayBase(void) = default;

      virtual void update(void) = 0;

    protected:
      Util::Memory::S_ptr<LiquidCrystal>& get_screen(void);

    private:
      Util::Memory::S_ptr<LiquidCrystal> _screen{ };
    };
  }
}