#pragma once
#include "InputBase.hpp"

namespace InOut
{
  namespace Analog
  {
    /**
     * Facade for managing analog inputs on Arduino boards.
     */
    class AnalogInput : public InputBase
    {
    public:
      AnalogInput(int pin_number);
      virtual ~AnalogInput(void) = default;
      
      bool is_active(void) const override;

    protected:
      virtual int do_read_value(void) override;
    };
  }
}