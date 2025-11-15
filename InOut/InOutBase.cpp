#include "InOutBase.hpp"

/**
 * Give this as an argument to concrete implementations that do not
 * require a physical pin, like composites or decorators.
 */
const int InOut::InOutBase::NO_PIN_AFFECTED{ -1 };

/**
 * Initializes this InOutBase with the provided pin number.
 * @param pin_number must correspond to a physical pin on the Arduino board.
 */
InOut::InOutBase::InOutBase(int pin_number) 
  : _pin_number{ pin_number }
  , StateChanged{ new Util::Event::EventHandler<const InOutBase, int> }
{
  // Empty body
}

/**
 * @return this InOutBase's _pin_number member value.
 */
int InOut::InOutBase::get_pin_number(void) const
{
  return _pin_number;
}

/**
 * @return this InOutBase's _current_state member value.
 */
int InOut::InOutBase::get_current_state(void) const
{
  return _current_state;
}

/**
 * Sets the _current_state member to the provided value.
 * @param current_state must be a coherent value, depending
 *                      on the concrete type of InOutBase.
 */
void InOut::InOutBase::set_current_state(int current_state)
{
  if (_current_state != current_state)
  {
    _current_state = current_state;
    StateChanged->call(this, current_state);
  }
}