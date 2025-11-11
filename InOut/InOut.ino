#include "AnalogInput.hpp"
#include "Speaker.hpp"
#include "InOutFactory.hpp"
#include <S_ptr.hpp>

Util::Memory::S_ptr<InOut::Sound::Speaker> speaker{ };
bool is_incrementing{ };
int current_frequency;

void setup() {
  // put your setup code here, to run once:
  speaker = InOut::Factory::InOutFactory::create_speaker(8);
  current_frequency = InOut::Sound::Speaker::MIN_FREQUENCY;
  Serial.begin(9600);
}

void loop() {
  if (current_frequency >= InOut::Sound::Speaker::MAX_FREQUENCY)
  {
    is_incrementing = false;
  }
  if (current_frequency <= InOut::Sound::Speaker::MIN_FREQUENCY)
  {
    is_incrementing = true;
  }

  // speaker->write_value(current_frequency);
  Serial.println(is_incrementing ? current_frequency++ : current_frequency--);
}