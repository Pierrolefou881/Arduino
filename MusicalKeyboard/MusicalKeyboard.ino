#include <AnalogInput.hpp>
#include <InOutFactory.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <Callback.hpp>
#include <CallbackFactory.hpp>

class Keyboard
{
public:
  Keyboard(int keys_pin, int speaker_pin)
    : _keys{ InOut::Factory::InOutFactory::create_analog_input(keys_pin) }
    , _speaker{ InOut::Factory::InOutFactory::create_speaker(speaker_pin) }
  {
    _keys->StateChanged = Util::Event::CallbackFactory::create_callback(this, &Keyboard::on_key_pressed);
  }

  void tick(void)
  {
    _keys->read_value();
    _speaker->write_value(_pressed_note);
  }

private:
  static const int C{ 262 };
  static const int D{ 294 };
  static const int E{ 330 };
  static const int F{ 349 };
  Util::Memory::S_ptr<InOut::Analog::AnalogInput> _keys{ };
  Util::Memory::S_ptr<InOut::Sound::Speaker> _speaker{ };
  int _pressed_note {};

  void on_key_pressed(const InOut::InOutBase* sender, int args)
  {
    if (args > 1010)
    {
      _pressed_note = C;
    }
    else if (args > 600)
    {
      _pressed_note = D;
    }
    else if (args > 50)
    {
      _pressed_note = E;
    }
    else if (args > 5)
    {
      _pressed_note = F;
    }
    else
    {
      _pressed_note = 0;
    }
    Serial.println(args);
  }
};

Util::Memory::U_ptr<Keyboard> kb{ };

void setup() {
  // put your setup code here, to run once:
  kb = new Keyboard{ A0, 12 };
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  kb->tick();
}
