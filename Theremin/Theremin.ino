#include "Theremin.hpp"
#include <U_ptr.hpp>
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
#include <CallbackFactory.hpp>

struct StatusLed
{
  Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _led{ };
  StatusLed(int pin_number) : _led{ InOut::Factory::InOutFactory::create_digital_output(pin_number) } {}
  void system_status_changed(const Music::Theremin* sender, int args)
  {
    _led->write_value(args);
  }
};

Util::Memory::U_ptr<Music::Theremin> theremin{ };
Util::Memory::U_ptr<StatusLed> status_led{ };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  theremin = new Music::Theremin{ A0, 8 };
  status_led = new StatusLed{ LED_BUILTIN };
  theremin->CalibrationStatusChanged = Util::Event::CallbackFactory::create_callback(status_led.get(), &StatusLed::system_status_changed);
}

void loop() {
  // put your main code here, to run repeatedly:
  theremin->calibrate(millis());
  theremin->actuate();
}
