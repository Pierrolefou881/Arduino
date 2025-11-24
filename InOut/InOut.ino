#include "DigitalInput.hpp"
#include "DigitalOutput.hpp"
#include "AnalogInput.hpp"
#include "PWMOutput.hpp"
#include "Speaker.hpp"
#include "MemorySwitch.hpp"
#include "CapacitiveInput.hpp"
#include "InOutFactory.hpp"
#include <S_ptr.hpp>

Util::Memory::S_ptr<InOut::Analog::CapacitiveInput> touch_switch{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };

void setup() {
  // put your setup code here, to run once:
  touch_switch = new InOut::Analog::CapacitiveInput{ 8, 12 };
  led = InOut::Factory::InOutFactory::create_digital_output(2);
  Serial.begin(9600);
}

void loop() {
  auto value = touch_switch->read_value();
  if (touch_switch->is_active())
  {
    led->turn_on();
  }
  else 
  {
    led->turn_off();
  }
  Serial.println(value);
}