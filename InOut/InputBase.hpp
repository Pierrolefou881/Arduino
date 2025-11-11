#pragma once

#include "InOutBase.hpp"

namespace InOut
{
  /**
   * Base class defining the behavior for Arduino inputs.
   * Inputs should be able to read their value and
   * express whether they are active or not.
   */
  class InputBase : public InOutBase
  {
    public:
    InputBase(int pin_number);
    virtual ~InputBase(void) = default;

    int read_value(void);
    virtual bool is_active(void) const = 0;

    protected:
    virtual int do_read_value(void) = 0;
  };
}