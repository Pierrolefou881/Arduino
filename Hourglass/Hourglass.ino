#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Timer.hpp>
#include <DigitalOutput.hpp>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>

Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_button{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_button{ };

void setup() {
  // put your setup code here, to run once:
  start_button = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_button = InOut::Factory::InOutFactory::create_digital_input(11);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto start = start_button->read_value();
  auto reset = reset_button->read_value();
  Serial.println(start + reset);
}