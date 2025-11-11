#include "InputBase.hpp"

/**
 * Initializes this InputBase with the provided pin number.
 * @param pin_number must correspond to a physical pin on the board.
 */
InOut::InputBase::InputBase(int pin_number) : InOut::InOutBase::InOutBase{ pin_number }
{
  // Empty body
}

/**
 * Reads the value currently at this InputBase's _pin_number
 * and actuates its state accordingly.
 */
int InOut::InputBase::read_value(void)
{
  auto new_state = do_read_value();
  set_current_state(new_state);
  return new_state;
}