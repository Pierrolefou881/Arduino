#pragma once
#include "DisplayBase.hpp"
#include <S_ptr.hpp>

class LiquidCrystal;

namespace Time
{
  class Calendar;
}

namespace DigitalClock
{
  namespace Display
  {
    class DateDisplay : public DisplayBase
    {
    public:
      DateDisplay(const Util::Memory::S_ptr<LiquidCrystal>& screen,
                  const Util::Memory::S_ptr<Time::Calendar>& calendar);
      virtual ~DateDisplay(void);

      void update(void) override;
    private:
      Util::Memory::S_ptr<Time::Calendar> _calendar{ };
    };
  }
}