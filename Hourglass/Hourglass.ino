#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Timer.hpp>
#include <DigitalOutput.hpp>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <CallbackFactory.hpp>
#include "HourglassDisplay.hpp"

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_button{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_button{ };
Util::Memory::U_ptr<InOut::Digital::HourglassDisplay> display{ };
Util::Memory::U_ptr<Time::Timer> timer{ };


void setup() {
  // put your setup code here, to run once:
  // Back end
  timer = new Time::Timer{ };
  Time::TimeData settings{ };
  settings.minute = 59;
  settings.second = 59;
  settings.millisecond = 999;
  timer->set_time_stamp(settings);

  // Output
  display = new InOut::Digital::HourglassDisplay{ 2, 3, 4, 5, 6, 7, LED_BUILTIN };

  timer->MinuteElapsed = Util::Event::CallbackFactory::create_callback(display.get(), &InOut::Digital::HourglassDisplay::on_minute_elapsed);
  timer->SecondElapsed = Util::Event::CallbackFactory::create_callback(display.get(), &InOut::Digital::HourglassDisplay::on_second_elapsed);

  timer->start();
  // Input
  start_button = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_button = InOut::Factory::InOutFactory::create_digital_input(11);
  start_button->StateChanged = Util::Event::CallbackFactory::create_callback(&toggle_leds);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer->tick(millis());
  auto start = start_button->read_value();
  auto reset = reset_button->read_value();
  Serial.println(start + reset);
}

void toggle_leds(const InOut::InOutBase* sender, int args)
{
  display->write_value(args);
}