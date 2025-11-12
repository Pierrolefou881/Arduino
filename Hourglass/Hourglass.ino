#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Timer.hpp>
#include <DigitalOutput.hpp>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <CallbackFactory.hpp>

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_button{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_button{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> red{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> yellow1{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> yellow2{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> green1{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> green2{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> blue{ };

void setup() {
  // put your setup code here, to run once:
  start_button = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_button = InOut::Factory::InOutFactory::create_digital_input(11);
  blue = InOut::Factory::InOutFactory::create_digital_output(2);
  green1 = InOut::Factory::InOutFactory::create_digital_output(3);
  green2 = InOut::Factory::InOutFactory::create_digital_output(4);
  yellow1 = InOut::Factory::InOutFactory::create_digital_output(5);
  yellow2 = InOut::Factory::InOutFactory::create_digital_output(6);
  red = InOut::Factory::InOutFactory::create_digital_output(7);

  start_button->StateChanged = Util::Event::CallbackFactory::create_callback(&toggle_leds);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto start = start_button->read_value();
  auto reset = reset_button->read_value();
  Serial.println(start + reset);
}

void toggle_leds(const InOut::InOutBase* sender, int args)
{
  red->write_value(args);
  yellow1->write_value(args);
  yellow2->write_value(args);
  green1->write_value(args);
  green2->write_value(args);
  blue->write_value(args);
}