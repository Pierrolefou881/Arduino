#pragma once
#include "OutputBase.hpp"

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }
  
  namespace Digital
  {
    /**
     * Façade managing Arduino boards' digital output pins.
     * Can send a value either HIGH or LOW to the corresponding
     * pin on the board.
     */
    class DigitalOutput : public OutputBase
    {
      public:
        virtual ~DigitalOutput(void) = default;

        void write_value(int value) override;
        void turn_on(void);
        void turn_off(void);
        void toggle(void);

        friend class InOut::Factory::InOutFactory;

      private:
        DigitalOutput(int pin_number);
    };
  }
}