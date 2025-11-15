// #define _STOPWATCH
#define _TIMER
#define _METHOD

#include "BaseClock.hpp"
#include "Stopwatch.hpp"
#include "Timer.hpp"
#include <DigitalOutput.hpp>
#include <Speaker.hpp>
#include <InOutFactory.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <CallbackFactory.hpp>
#include "EventHandler.hpp"

class Blinker
{
public:
  Util::Memory::S_ptr<InOut::Digital::DigitalOutput> _led{ };
  virtual ~Blinker(void) = default;
  void toggle(const Time::BaseClock* clk, const Time::TimeData& data)
  {
    if (_led != nullptr)
      _led->toggle();
  }
};

class Buzzer
{
public:
  Util::Memory::S_ptr<InOut::Sound::Speaker> speaker{ };
  bool is_active;

  virtual ~Buzzer(void) = default;
  void on_timer_elapsed(const Time::Timer* timer, void* args)
  {
    is_active = true;
    Serial.println("TIME UP !");
  }
};

Util::Memory::U_ptr<Blinker> blk{ };
Util::Memory::U_ptr<Blinker> blue_blk{ };
Util::Memory::U_ptr<Buzzer> buzz{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> blue{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> red{ };
Util::Memory::U_ptr<Time::BaseClock> clk{ };

void setup() {
  Serial.begin(9600);
  led = InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN);
  blue = InOut::Factory::InOutFactory::create_digital_output(2);
  red = InOut::Factory::InOutFactory::create_digital_output(7);
  buzz = new Buzzer{ };
  buzz->speaker = InOut::Factory::InOutFactory::create_speaker(8);

  #ifdef _STOPWATCH
  clk = new Time::Stopwatch{ };
  static_cast<Time::Stopwatch*>(clk.get())->start();

  #elif defined(_TIMER)
  clk = new Time::Timer{ };
  Time::TimeData setting{ };
  setting.hour = 0;
  setting.minute = 0;
  setting.second = 15;
  clk->set_time_stamp(setting);
  static_cast<Time::Timer*>(clk.get())->CountdownComplete->add(buzz.get(), &Buzzer::on_timer_elapsed);
  static_cast<Time::Timer*>(clk.get())->start();

  #else
  clk = new Time::BaseClock();
  Time::TimeData current_time{ };
  current_time.hour = 11;
  current_time.minute = 21;
  clk->set_time_stamp(current_time);
  #endif

  #ifdef _METHOD
  blk = new Blinker{ };
  blue_blk = new Blinker{ };
  blk->_led = led;
  blue_blk->_led = blue;
  clk->SecondElapsed->add(blk.get(), &Blinker::toggle);
  clk->SecondElapsed->add(blue_blk.get(), &Blinker::toggle);
  clk->SecondElapsed->add(&toggle_led);
  #else
  clk->SecondElapsed->add(&toggle_led);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  clk->tick(millis());
  auto time_stamp = clk->get_time_stamp();
  Serial.print(time_stamp.hour);
  Serial.print("H\t");
  Serial.print(time_stamp.minute);
  Serial.print("M\t");
  Serial.print(time_stamp.second);
  Serial.print("S\t");
  Serial.println(time_stamp.millisecond);
  if (buzz->is_active)
  {
    buzz->speaker->write_value(440);
  }
  delay(250);
}

void toggle_led(const Time::BaseClock* clock, const Time::TimeData& time_stamp)
{
  red->toggle();
  Serial.println("SECOND");
}
