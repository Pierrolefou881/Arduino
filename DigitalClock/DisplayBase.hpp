#pragma once

#include <S_ptr.hpp>

class LiquidCrystal;

namespace DigitalClock
{
  namespace Display
  {
    /**
     * Abstract implementation for basic display behaviors
     * using LCD screens. Should not be instanced directly
     */
    class DisplayBase
    {
    public:
      virtual ~DisplayBase(void) = default;

      virtual void update(void);

    protected:
      DisplayBase(const Util::Memory::S_ptr<LiquidCrystal>& screen);

      Util::Memory::S_ptr<LiquidCrystal>& get_screen(void);

    private:
      Util::Memory::S_ptr<LiquidCrystal> _screen{ };
    };
  }
}