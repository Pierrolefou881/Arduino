#include <MemorySwitch.hpp>
#include <AnalogInput.hpp>
#include <DigitalOutput.hpp>
#include <PWMOutput.hpp>
#include <InOutFactory.hpp>
#include <EventHandler.hpp>
#include <S_ptr.hpp>

Util::Memory::S_ptr<InOut::Digital::MemorySwitch> power_btn{ };
Util::Memory::S_ptr<InOut::Digital::MemorySwitch> direction_btn{ };
Util::Memory::S_ptr<InOut::Analog::AnalogInput> speed_pot{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> control_1{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> control_2{ };
Util::Memory::S_ptr<InOut::Analog::PWMOutput> enable{ };

void setup() {
  // put your setup code here, to run once:
  power_btn = InOut::Factory::InOutFactory::create_memory_switch(13);
  direction_btn = InOut::Factory::InOutFactory::create_memory_switch(12);
  speed_pot = InOut::Factory::InOutFactory::create_analog_input(A0);
  control_1 = InOut::Factory::InOutFactory::create_digital_output(3);
  control_2 = InOut::Factory::InOutFactory::create_digital_output(2);
  enable = InOut::Factory::InOutFactory::create_pwm_output(9);

  power_btn->StateChanged->add(&on_power_switch);
  direction_btn->StateChanged->add(&on_direction_change);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(power_btn->read_value());
  Serial.print('\t');
  Serial.print(direction_btn->read_value());
  Serial.print('\t');
  Serial.println(speed_pot->read_value());
  
  auto speed = speed_pot->read_value() / 4;
  enable->write_value(speed);
}

void on_power_switch(const InOut::InOutBase* sender, int args)
{
  if (args == LOW)
  {
    control_1->turn_off();
    control_2->turn_off();
    return;
  }

  if (direction_btn->read_value() >= HIGH)
  {
    control_1->toggle();
  }
  else
  {
    control_2->toggle();
  }
}

void on_direction_change(const InOut::InOutBase* sender, int args)
{
  control_1->toggle();
  control_2->toggle();
}
