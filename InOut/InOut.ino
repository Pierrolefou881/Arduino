#include "DigitalInput.hpp"
#include "DigitalOutput.hpp"
#include "AnalogInput.hpp"
#include "PWMOutput.hpp"
#include "Speaker.hpp"
#include "MemorySwitch.hpp"
#include "CapacitiveInput.hpp"
#include "CapacitiveDigitalInput.hpp"
#include "InOutFactory.hpp"
#include <S_ptr.hpp>

Util::Memory::S_ptr<InOut::Analog::CapacitiveInput> touch_switch{ };
Util::Memory::S_ptr<InOut::Digital::CapacitiveDigitalInput> digital_touch{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };

void setup() {
  // put your setup code here, to run once:
  // touch_switch = InOut::Factory::InOutFactory::create_capacitive_input(8, 12);
  digital_touch = InOut::Factory::InOutFactory::create_capacitive_digital_input(8, 12);
  led = InOut::Factory::InOutFactory::create_digital_output(2);
  Serial.begin(9600);
}

void loop() {
  led->write_value(digital_touch->read_value());
  // Serial.println(touch_switch->read_value());
}