// #define _STOPWATCH
#define _TIMER
#define _METHOD

#include "BaseClock.hpp"
#include "Stopwatch.hpp"
#include "Timer.hpp"
#include <DigitalOutput.hpp>
#include <Speaker.hpp>
#include <DigitalInput.hpp>
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
Util::Memory::U_ptr<Buzzer> buzz{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };
Util::Memory::U_ptr<Time::BaseClock> clk{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> start_btn{ };
Util::Memory::S_ptr<InOut::Digital::DigitalInput> reset_btn{ };

void setup() {
  Serial.begin(9600);
  led = InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN);
  buzz = new Buzzer{ };
  buzz->speaker = InOut::Factory::InOutFactory::create_speaker(8);
  start_btn = InOut::Factory::InOutFactory::create_digital_input(12);
  reset_btn = InOut::Factory::InOutFactory::create_digital_input(11);

  #ifdef _STOPWATCH
  clk = new Time::Stopwatch{ };
  start_btn->StateChanged->add(&start_pressed);
  reset_btn->StateChanged->add(&reset_pressed);

  #elif defined(_TIMER)
  start_btn->StateChanged->add(&start_pressed);
  reset_btn->StateChanged->add(&reset_pressed);
  clk = new Time::Timer{ };
  Time::TimeData setting{ };
  setting.hour = 0;
  setting.minute = 0;
  setting.second = 15;
  clk->set_time_stamp(setting);
  auto tm = static_cast<Time::Timer*>(clk.get());
  tm->CountdownComplete->add(buzz.get(), &Buzzer::on_timer_elapsed);

  #else
  clk = new Time::BaseClock();
  Time::TimeData current_time{ };
  current_time.hour = 11;
  current_time.minute = 21;
  clk->set_time_stamp(current_time);
  #endif

  #ifdef _METHOD
  blk = new Blinker{ };
  blk->_led = led;
  clk->SecondElapsed->add(blk.get(), &Blinker::toggle);
  #else
  clk->SecondElapsed->add(&toggle_led);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  clk->tick(millis());
  start_btn->read_value();
  reset_btn->read_value();
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
  delay(100);
}

void toggle_led(const Time::BaseClock* clock, const Time::TimeData& time_stamp)
{
  led->toggle();
  Serial.println("SECOND");
}

void start_pressed(const InOut::InOutBase* sender, int args)
{
  Serial.println("START / STOP");
  if (args == LOW)
  {
    return;
  }
  auto sw = static_cast<Time::Stopwatch*>(clk.get());
  
  if (sw->is_running())
  {
    sw->stop();
  }
  else 
  {
    sw->start();
  }
}

void reset_pressed(const InOut::InOutBase* sender, int args)
{
  if (args == LOW)
  {
    return;
  }
auto sw = static_cast<Time::Stopwatch*>(clk.get());
#ifdef _STOPWATCH
  if (sw->is_running())
  {
    sw->stop();
  }
  else 
  {
    sw->reset();
  }

#else
  sw->stop();
  sw->reset();
#endif
}