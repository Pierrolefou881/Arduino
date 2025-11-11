#include "InOutBase.hpp"

/**
 * Initializes this InOutBase with the provided pin number.
 * @param pin_number must correspond to a physical pin on the Arduino board.
 */
InOut::InOutBase::InOutBase(int pin_number)
{
  _pin_number = pin_number;
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
    on_state_changed();
  }
}

void InOut::InOutBase::on_state_changed(void) const
{
  if (StateChanged)
  {
    StateChanged->call(this, _current_state);
  }
}