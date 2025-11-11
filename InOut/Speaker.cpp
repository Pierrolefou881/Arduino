#include "Arduino.h"
#include "Speaker.hpp"

/** Minimal frequency that can be played by this Speaker, in Hz */
const int InOut::Sound::Speaker::MIN_FREQUENCY{ 50 };

/** Maximal frequency that can be played by this Speaker, in Hz */
const int InOut::Sound::Speaker::MAX_FREQUENCY{ 4000 };

/** Default duration for a sound, in mS*/
const int InOut::Sound::Speaker::DEFAULT_DURATION_MS{ 20 };

/**
 * Initializes this Speaker with the provided pin number and sound duration.
 * If no sound duration is provided, a default one is initialized.
 * @param pin_number must correspond to a physical digital output on the board.
 * @param sound_duration in mS. Defaulted if not provided.
 */
InOut::Sound::Speaker::Speaker(int pin_number, int sound_duration) : InOut::OutputBase{ pin_number }
  , _sound_duration{ sound_duration }
{
  // Empty body
}

/**
 * Emits a sound correponding to the given frequency.
 * @param value frequency of the sound, in Hz.
 */
void InOut::Sound::Speaker::write_value(int value)
{
  if (value < MIN_FREQUENCY)
  {
    
  }

  if (value > MAX_FREQUENCY)
  {
    value = MAX_FREQUENCY;
  }

  set_current_state(value);
  tone(get_pin_number(), value, _sound_duration);
}