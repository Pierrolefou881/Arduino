#include "OutputBase.hpp"

/**
 * Initializes this OutputBase with the provided pin number.
 * @param pin_number must correspond to a physical pin on the board.
 */
InOut::OutputBase::OutputBase(int pin_number) : InOut::InOutBase::InOutBase{ pin_number }
{
  // Empty body 
}