#include "Thermometer.hpp"
#include <U_ptr.hpp>
#include <S_ptr.hpp>
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>

Util::Memory::U_ptr<Sensor::Thermometer> _thermo{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _green{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _red{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _crimson{ };

void setup() {
  // put your setup code here, to run once:
  _thermo = new Sensor::Thermometer(A0);
  _green = InOut::Factory::InOutFactory::create_digital_output(6);
  _red = InOut::Factory::InOutFactory::create_digital_output(7);
  _crimson = InOut::Factory::InOutFactory::create_digital_output(8);
  _green->turn_on();
  _red->turn_off();
  _crimson->turn_off();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto temp = _thermo->read_celsius();
  Serial.print(_thermo->read_celsius());
  Serial.print(temp);
  Serial.print('\t');
  Serial.print(_thermo->read_farenheit());
  Serial.print('\t');
  Serial.println(_thermo->read_kelvin());

  if (temp >= 20.0f && temp < 24.0f)
  {
    _red->turn_on();
    _crimson->turn_off();
  }
  else if (temp >= 24.0f)
  {
    _red->turn_on();
    _crimson->turn_on();
  }
  else
  {
    _red->turn_off();
    _crimson->turn_off();
  }

  delay(1500);
}
