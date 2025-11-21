#include <LiquidCrystal.h>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <BaseClock.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <EventHandler.hpp>
#include "TimeDisplay.hpp"

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_btn{};
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_btn{};
Util::Memory::S_ptr<InOut::Digital::DigitalInput> mode_btn{};
Util::Memory::S_ptr<Time::BaseClock> clk{};
Util::Memory::S_ptr<LiquidCrystal> screen{};
Util::Memory::U_ptr<DigitalClock::Display::TimeDisplay> time_display{};


void setup() {
  // put your setup code here, to run once:
  start_btn = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_btn = InOut::Factory::InOutFactory::create_digital_input(13);
  mode_btn = InOut::Factory::InOutFactory::create_digital_input(9);
  clk = new Time::BaseClock{};

  screen = new LiquidCrystal{ 2, 11, 4, 5, 6, 7 };
  screen->begin(16, 2);
  screen->setCursor(4, 1);
  screen->print("00:00:00");

  time_display = new DigitalClock::Display::TimeDisplay{ screen, clk };
}

void loop() {
  // put your main code here, to run repeatedly:
  clk->tick(millis());

  auto start = start_btn->read_value();
  auto reset = reset_btn->read_value();
  auto mode = mode_btn->read_value();
}