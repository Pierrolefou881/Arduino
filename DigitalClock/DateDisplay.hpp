#pragma once
#include "DisplayBase.hpp"
#include <S_ptr.hpp>

class LiquidCrystal;

namespace Sensor
{
  class Thermometer;
  struct TemperatureData;
}

namespace Time
{
  struct DateData;
  class Calendar;
}

namespace DigitalClock
{
  namespace Display
  {
    /**
     * Displays the date from a calendar on a LCD screen.
     * Displays also room temperature in Celsius or Farenheit.
     */
    class DateDisplay : public DisplayBase
    {
    public:
      DateDisplay(const Util::Memory::S_ptr<LiquidCrystal>& screen,
                  const Util::Memory::S_ptr<Time::Calendar>& calendar,
                  int screen_width = 16);
      virtual ~DateDisplay(void);

    private:
      static const char* DAY_NAMES[];
      static const int DISPLAY_ROW;
      static const char SEPARATOR;
      static const int DISPLAY_WIDTH;
      
      Util::Memory::S_ptr<Time::Calendar> _calendar{ };
      int _day_name_index{ };
      int _day_number_index{ };
      int _month_index{ };
      int _year_index{ };

      void write(int desired_index, int value);
      void print_week_day(int week_day);

      void on_day_elapsed(const Time::Calendar* sender, const Time::DateData& args);
      void on_month_elapsed(const Time::Calendar* sender, const Time::DateData& args);
      void on_year_elapsed(const Time::Calendar* sender, const Time::DateData& args);
    };
  }
}