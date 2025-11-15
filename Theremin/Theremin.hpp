#pragma once
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <AnalogInput.hpp>
#include <Speaker.hpp>
#include <Timer.hpp>
#include <EventHandler.hpp>

namespace Music
{
  class Theremin
  {
  public:
    Util::Memory::U_ptr<Util::Event::EventHandler<const Theremin, int>> CalibrationStatusChanged{ };

    Theremin(int sensor_pin, int speaker_pin, int sound_duration = InOut::Sound::Speaker::DEFAULT_DURATION_MS);
    virtual ~Theremin(void) = default;

    void calibrate(unsigned long time_ms);
    void actuate(void);
    bool is_calibrated(void) const;

  private:
    static const int CALIBRATION_DELAY_S;
    static const int CALIBRATION_ACTIVE;
    static const int CALIBRATION_COMPLETE;

    Util::Memory::S_ptr<InOut::Analog::AnalogInput> _sensor{ };
    Util::Memory::S_ptr<InOut::Sound::Speaker> _speaker{ };
    Util::Memory::U_ptr<Time::Timer> _calibration_timer{ };

    bool _is_calibrated{ };

    int _lower_threshold{ };
    int _uppper_threshold{ };
    
    void play_note(const InOut::InOutBase* sender, int args);
    void calibration_timer_expired(const Time::Timer* sender, void* args);
  };
}