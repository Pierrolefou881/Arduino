#include "BaseClock.hpp"
#pragma once

#include <OutputBase.hpp>
#include <S_ptr.hpp>
#include <ArrayList.hpp>
#include <Timer.hpp>

namespace InOut
{
  namespace Digital
  {
    class HourglassDisplay : public OutputBase
    {
    public:
      HourglassDisplay(int blue, int low_green, int high_green, int low_yellow, int high_yellow, int red, int seconds);
      virtual ~HourglassDisplay(void) = default;

      void write_value(int value) override;
      void on_minute_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
      void on_second_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);

    private:
      static const int SIZE;
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _blue{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _low_green{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _high_green{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _low_yellow{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _high_yellow{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _red{ };
      Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _seconds{ };
    };
  }
}