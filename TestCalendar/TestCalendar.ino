#include <BaseClock.hpp>
#include <Calendar.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <EventHandler.hpp>

Util::Memory::S_ptr<Time::BaseClock> clk{ };
Util::Memory::U_ptr<Time::Calendar> cal{ };

void setup() {
  // put your setup code here, to run once:
  clk = new Time::BaseClock{ };
  cal = new Time::Calendar{ };
  cal->assign_clock(clk);
  cal->DayElapsed->add(&calendar_updated);
  delay(5);
  cal->MonthElapsed->add(&calendar_updated);
  delay(5);
  cal->YearElapsed->add(&calendar_updated);
  delay(5);
  clk->HourElapsed->add(&hour_elapsed);
  delay(5);
  Serial.begin(9600);
  Serial.println("TEST STARTED");
}

void loop() {
  // put your main code here, to run repeatedly:
  clk->tick(millis() * 20000);
}

void hour_elapsed(const Time::BaseClock* sender, const Time::TimeData& args)
{
  print_time_and_date(cal->get_date_stamp(), args);
}

void calendar_updated(const Time::Calendar* sender, const Time::DateData& args)
{
  print_time_and_date(args, clk->get_time_stamp());
}

void print_time_and_date(const Time::DateData& date, const Time::TimeData& time)
{
  Serial.print("Y");
  Serial.print(date.year);
  Serial.print("\tM");
  Serial.print(date.month);
  Serial.print("\tD");
  Serial.print(date.day);
  Serial.print("\tH");
  Serial.print(time.hour);
  Serial.print("\tm");
  Serial.println(time.minute);
}

void blink(const Time::BaseClock* sender, const Time::TimeData& args)
{
  Serial.println("S");
}
