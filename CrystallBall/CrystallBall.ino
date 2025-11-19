#include <LiquidCrystal.h>
#include <DigitalInput.hpp>
#include <InOutFactory.hpp>
#include <S_ptr.hpp>
#include <EventHandler.hpp>
#include <Timer.hpp>

const char* text[] = { "Ask the ball:", "Yes", "Most likely", "Certainly", "Outlook good", "Unsure", "Ask again", "Meh", "Nope" };
LiquidCrystal lcd(2, 11, 4, 5, 6, 7);
Util::Memory::S_ptr<InOut::Digital::DigitalInput> btn{ };
Util::Memory::U_ptr<Time::Timer> tim{ };
bool can_interact{ };

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  prompt(nullptr, nullptr);
  btn = InOut::Factory::InOutFactory::create_digital_input(13);
  btn->StateChanged->add(&ask_ball);
  tim = new Time::Timer{ };
  Time::TimeData settings{ };
  settings.second = 3;
  tim->set_time_stamp(settings);
  tim->CountdownComplete->add(&prompt);
  can_interact = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  btn->read_value();
  tim->tick(millis());
}

void prompt(const Time::Timer* sender, void* args)
{
  lcd.clear();
  lcd.print(text[0]);
  can_interact = true;
}

void ask_ball(const InOut::InOutBase* sender, int args)
{
  if(args == LOW || !can_interact)
  {
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print(text[random(8) + 1]);
  tim->reset();
  tim->start();
  can_interact = false;
}
