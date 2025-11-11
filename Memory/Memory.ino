#define _TEST
#define _TEST_TRANSFERT
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
// #include "U_ptr.hpp"

#include "S_ptr.hpp"

// Util::Memory::U_ptr<InOut::Digital::DigitalOutput> led{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };
// Util::Memory::U_ptr<InOut::Digital::DigitalOutput> null{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> null{ };

// Util::Memory::U_ptr<InOut::Digital::DigitalOutput> create_digital_output(void)
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> create_digital_output(void)
{
  // return Util::Memory::U_ptr<InOut::Digital::DigitalOutput>(InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN));
  return Util::Memory::S_ptr<InOut::Digital::DigitalOutput>(InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN));
}

void setup() {
  // put your setup code here, to run once:
  // led = create_digital_output();
  Serial.begin(9600);

  #ifdef _TEST_TRANSFERT
  auto tmp = create_digital_output();
  led = create_digital_output();
  null = tmp;
  Serial.println(tmp.get_reference_count());
  Serial.println(led.get_reference_count());
  Serial.println("TEST TRANSFERT");
  #else
  auto ptr = InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN);
  // Util::Memory::S_ptr<InOut::Digital::DigitalOutput> tmp { ptr };
  Util::Memory::S_ptr<InOut::Digital::DigitalOutput> tmp = ptr;
  auto copy = tmp;
  led = tmp;
  Serial.println(tmp.get_reference_count());
  Serial.println(tmp.get_reference_count());
  #endif


}

void loop() {
  null = nullptr;
  Serial.println(null.get_reference_count());
  Serial.println(led.get_reference_count());
  // put your main code here, to run repeatedly:
  // Serial.print("led is null -> ");
  // Serial.println(led == nullptr);
  // Serial.print("null is null -> ");
  // Serial.println(null == nullptr);
  led->toggle();
  delay(1000);
}

