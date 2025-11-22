#include <LiquidCrystal.h>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <BaseClock.hpp>
#include <Calendar.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <EventHandler.hpp>
#include "TimeDisplay.hpp"
#include "DateDisplay.hpp"

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_btn{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_btn{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> mode_btn{ };
Util::Memory::S_ptr<Time::BaseClock> clk{ };
Util::Memory::S_ptr<Time::Calendar> cal{ };
Util::Memory::S_ptr<LiquidCrystal> screen{ };
Util::Memory::U_ptr<DigitalClock::Display::TimeDisplay> time_display{ };
Util::Memory::U_ptr<DigitalClock::Display::DateDisplay> date_display{ };

void setup() {
  // put your setup code here, to run once:
  start_btn = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_btn = InOut::Factory::InOutFactory::create_digital_input(13);
  mode_btn = InOut::Factory::InOutFactory::create_digital_input(9);
  clk = new Time::BaseClock{ };
  Time::TimeData time{ };
  time.hour = 18;
  time.minute = 30;
  clk->set_time_stamp(time);
  cal = new Time::Calendar{ clk };
  Time::DateData date{ };
  date.year = 2025;
  date.month = 11;
  date.day = 22;
  cal->set_date_stamp(date);
  screen = new LiquidCrystal{ 2, 11, 4, 5, 6, 7 };
  screen->begin(16, 2);

  time_display = new DigitalClock::Display::TimeDisplay{ screen, clk };
  date_display = new DigitalClock::Display::DateDisplay{ screen, cal };
}

void loop() {
  // put your main code here, to run repeatedly:
  clk->tick(millis());
  // temperature_display->update();

  auto start = start_btn->read_value();
  auto reset = reset_btn->read_value();
  auto mode = mode_btn->read_value();
}