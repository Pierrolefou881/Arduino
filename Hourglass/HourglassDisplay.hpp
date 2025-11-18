#include "LinkedList.hpp"
#include "ArrayList.hpp"
#pragma once
#include <OutputBase.hpp>
#include <S_ptr.hpp>

namespace Util
{
  namespace Collection
  {
    template<typename T>
    class LinkedList;
  }
}

namespace Time
{
  class BaseClock;
  struct TimeData;
}

namespace InOut
{
  namespace Digital
  {
    class DigitalOutput;

    class HourglassDisplay : public OutputBase
    {
    public:
      HourglassDisplay(Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>* leds);
      virtual ~HourglassDisplay(void) = default;

      void write_value(int value) override;
      void reset(void);
      void on_minute_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
      void on_second_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);

    private:
      Util::Memory::S_ptr<Util::Collection::BaseList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>> _leds{ };
      unsigned int _next_index{ };
    };
  }
}