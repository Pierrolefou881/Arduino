#pragma once
#include <U_ptr.hpp>
#include <EventHandler.hpp>

namespace InOut
{
  /**
   * Base class for defining Arduino Input and Output behavior.
   * Input and Output are both defined by a physical pin number
   * on the board and a state that should be altered through
   * the functionning of the device.
   */
  class InOutBase
  {
    public:
      static const int NO_PIN_AFFECTED;
      Util::Memory::U_ptr<Util::Event::EventHandler<const InOutBase, int>> StateChanged{ };

      virtual ~InOutBase(void) = default;
      int get_pin_number(void) const;

    protected:
      InOutBase(int pin_number);
      int get_current_state(void) const;
      void set_current_state(int current_state);

    private:
      int _pin_number{ };
      int _current_state{ };
  };
}