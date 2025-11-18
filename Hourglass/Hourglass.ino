#include "HourglassDisplay.hpp"
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Stopwatch.hpp>
#include <LinkedList.hpp>
#include <ArrayList.hpp>
#include <DigitalOutput.hpp>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <EventHandler.hpp>

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_button{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_button{ };
Util::Memory::U_ptr<InOut::Digital::HourglassDisplay> display{ };
Util::Memory::U_ptr<Time::Stopwatch> stopwatch{ };

void setup() {
  // put your setup code here, to run once:
  // Back end
  stopwatch = new Time::Stopwatch{ };

  // Front end
  Util::Memory::U_ptr<Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>> led_pins{ new Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ } };
  led_pins->append(InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN));
  for (auto i = 2; i <= 7; i++)
  {
    led_pins->append(InOut::Factory::InOutFactory::create_digital_output(i));
  }
  display = new InOut::Digital::HourglassDisplay{ led_pins.get() };

  stopwatch->MinuteElapsed->add(display.get(), &InOut::Digital::HourglassDisplay::on_minute_elapsed);
  stopwatch->SecondElapsed->add(display.get(), &InOut::Digital::HourglassDisplay::on_second_elapsed);

  stopwatch->start();
  // Input
  start_button = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_button = InOut::Factory::InOutFactory::create_digital_input(11);
  start_button->StateChanged->add(&start_stop_clock);
  reset_button->StateChanged->add(&reset_clock);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  stopwatch->tick(millis());
  auto start = start_button->read_value();
  auto reset = reset_button->read_value();
  auto time_stamp = stopwatch->get_time_stamp();
  Serial.print(time_stamp.minute);
  Serial.print(" : ");
  Serial.print(time_stamp.second);
  Serial.print(" : ");
  Serial.println(time_stamp.millisecond);
  delay(500);
}

void start_stop_clock(const InOut::InOutBase* sender, int args)
{
  if (args == LOW)
  {
    return;
  }
  if (stopwatch->is_running())
  {
    stopwatch->stop();
  }
  else 
  {
    stopwatch->start();
  }
}

void reset_clock(const InOut::InOutBase* sender, int args)
{
  if (args > LOW)
  {
    stopwatch->reset();
    display->reset();
  }
}