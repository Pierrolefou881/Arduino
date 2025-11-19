#include <MemorySwitch.hpp>
#include <DigitalInput.hpp>
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
#include <S_ptr.hpp>

Util::Memory::S_ptr<InOut::Digital::MemorySwitch> mem_switch{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> motor{ };

void setup() {
  // put your setup code here, to run once:
  motor = InOut::Factory::InOutFactory::create_digital_output(9);
  mem_switch = InOut::Factory::InOutFactory::create_memory_switch(13);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto running_state = mem_switch->read_value();
  Serial.println(running_state);
  motor->write_value(running_state);
}
