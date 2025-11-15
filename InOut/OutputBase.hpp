#pragma once
#include "InOutBase.hpp"

namespace InOut
{
  /**
   * Defines basic behavior for Arduino outputs.
   * All outputs should be able to write a value
   * to their actuators.
   */
  class OutputBase : public InOutBase
  {
    public:
    OutputBase(int pin_number);
    virtual ~OutputBase(void) = default;

    virtual void write_value(int value) = 0;
  };
}