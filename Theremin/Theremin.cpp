#include "Theremin.hpp"
#include <InOutFactory.hpp>
#include "EventHandler.hpp"
#include <limits.h>
#include <Arduino.h>

const int Music::Theremin::CALIBRATION_DELAY_S{ 10 };
const int Music::Theremin::CALIBRATION_ACTIVE{ 1 };
const int Music::Theremin::CALIBRATION_COMPLETE{ 0 };

/**
 * Initializes this Theremin with the provided pin numbers for the light sensor
 * and the speaker. Speaker sound duration can also be provided; if not, speaker's
 * default shall be selected instead. Subscribes to the sensor's callback in order to
 * write down any change.
 */
Music::Theremin::Theremin(int sensor_pin, int speaker_pin, int sound_duration)
  : CalibrationStatusChanged{ new Util::Event::EventHandler<const Theremin, int>{ } }
  , _sensor{ InOut::Factory::InOutFactory::create_analog_input(sensor_pin) }
  , _speaker{ InOut::Factory::InOutFactory::create_speaker(speaker_pin, sound_duration) }
  , _lower_threshold{ INT_MAX }
  , _uppper_threshold{ 0 }
{
  _sensor->StateChanged->add(this, &Theremin::play_note);
}

/**
 * Launches and continues this Theremin's calibration sequence.
 * Should be called before playing the instrument. Can be either called
 * in a while statement:
 * while (!theremin->is_calibrated())
 * {
 *   theremin->calibrate(millis());
 * }
 *
 * or directly from the loop function:
 * theremin->calibrate(millis());
 * theremin->actuate();
 *
 * actuate method shall not play if theremin not calibrated.
 */
void Music::Theremin::calibrate(unsigned long time_ms)
{
  if (_is_calibrated) // Already calibrated, we're good to go.
  {
    return;
  }

  if (!_calibration_timer)
  {
    CalibrationStatusChanged->call(this, CALIBRATION_ACTIVE);
    _calibration_timer = new Time::Timer{ };
    Time::TimeData timer_duration{ };
    timer_duration.second = CALIBRATION_DELAY_S;
    _calibration_timer->set_time_stamp(timer_duration);
    _calibration_timer->CountdownComplete->add(this, &calibration_timer_expired);
    _calibration_timer->start();
  }

  _calibration_timer->tick(time_ms);
  auto sensor_value = _sensor->read_value();
  if (sensor_value > _uppper_threshold)
  {
    _uppper_threshold = sensor_value;
  }

  if (sensor_value < _lower_threshold)
  {
    _lower_threshold = sensor_value;
  }
}

/**
 * Requires the sensor to read its value. This method is necessary to trigger
 * the sensor's StateChanged event of which this Theremin is the subscriber.
 */
void Music::Theremin::actuate(void)
{
  if (_is_calibrated)
  {
    if (_calibration_timer) // Free memory if no more needed.
    {
      _calibration_timer = nullptr;
    }

    _sensor->read_value();
  }
}

/**
 * @param return true if this Theremin has been calibrated,
 *               false if it has not or it is being calibrated.
 */
bool Music::Theremin::is_calibrated(void) const
{
  return _is_calibrated;
}

void Music::Theremin::play_note(const InOut::InOutBase* sender, int args)
{
  if (_is_calibrated) 
  {
    auto pitch = map(args, _lower_threshold, _uppper_threshold, InOut::Sound::Speaker::MIN_FREQUENCY, InOut::Sound::Speaker::MAX_FREQUENCY);
    _speaker->write_value(pitch);
  }
}

void Music::Theremin::calibration_timer_expired(const Time::Timer* sender, void* args)
{
  _is_calibrated = true;
  CalibrationStatusChanged->call(this, CALIBRATION_COMPLETE);
}