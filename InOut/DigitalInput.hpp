#pragma once
#include "InputBase.hpp"

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }

  namespace Digital
  {
    /**
     * Façade for managing digital input pins on
     * Arduino boards. The digital input's state
     * is either HIGH or LOW.
     */
    class DigitalInput : public InputBase
    {
      public:
      virtual ~DigitalInput(void) = default;

      bool is_active(void) const override;

      friend class InOut::Factory::InOutFactory;

      protected:
      DigitalInput(int pin_number);
      int do_read_value(void) override;
    };
  }
}