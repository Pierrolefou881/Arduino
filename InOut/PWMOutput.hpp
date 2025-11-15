#pragma once
#include "OutputBase.hpp"

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }

  namespace Analog
  {
    /**
     * Facade managing PWM outputs for Arduino boards.
     * The actuator's state is an unsigned byte value (0 to 255).
     * PWMOutput shares the same interface as BaseOutput, with the
     * addition of a shutdown method
     */
    class PWMOutput : public OutputBase
    {
    public:
      virtual ~PWMOutput(void) = default;

      void write_value(int value) override;
      void shutdown(void);

      friend class InOut::Factory::InOutFactory;

      private:
      PWMOutput(int pin_number);
    };
  }
}