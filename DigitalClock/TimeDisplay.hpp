#pragma once
#include "DisplayBase.hpp"
#include <S_ptr.hpp>

class LiquidCrystal;

namespace Time
{
  class BaseClock;
  struct TimeData;
}

namespace DigitalClock
{
  namespace Display
  {
    class TimeDisplay : public DisplayBase
    {
    public:
      TimeDisplay(const Util::Memory::S_ptr<LiquidCrystal>& screen,
                  const Util::Memory::S_ptr<Time::BaseClock>& clock, 
                  int screen_width = 16);

      virtual ~TimeDisplay(void);

      void update(void) override;
      
    private:
      static const int DISPLAY_WIDTH;
      static const int DISPLAY_ROW;
      static const char SEPARATOR;

      Util::Memory::S_ptr<Time::BaseClock> _clock{ };
      int _hour_index{ };
      int _minute_index{ };
      int _second_index{ };

      void on_second_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
      void on_minute_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
      void on_hour_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);
      void on_day_elapsed(const Time::BaseClock* sender, const Time::TimeData& args);

      void write(int desired_index, int value);
    };
  }
}