#pragma once
#include "OutputBase.hpp"

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }

  namespace Sound
  {
    class Speaker : public OutputBase
    {
    public:
      static const int MIN_FREQUENCY;
      static const int MAX_FREQUENCY;
      static const int DEFAULT_DURATION_MS;

      virtual ~Speaker(void) = default;
      void write_value(int value) override;

      friend class InOut::Factory::InOutFactory;
    private:
      int _sound_duration{ };

      Speaker(int pin_number, int sound_duration = DEFAULT_DURATION_MS);
    };
  }
}