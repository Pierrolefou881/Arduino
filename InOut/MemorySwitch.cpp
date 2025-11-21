#include "MemorySwitch.hpp"
#include <Arduino.h>

/**
 * Initializes this memorySwitch with the provided pin number and
 * type of input that shall be attached to it. If no type is
 * provided, DIGITAL shall be default.
 * @param pin_number must correspond to the actual input pin on the board.
 * @param type of input used in this MemorySwitch.
 */
InOut::Digital::MemorySwitch::MemorySwitch(const Util::Memory::S_ptr<InOut::Digital::DigitalInput>& input)
  : DigitalInput{ input->get_pin_number() }, _in{ input }, _memory_state{ LOW }
{
  input->StateChanged->add(this, &InOut::Digital::MemorySwitch::on_input_state_changed);
}

/**
 * Actuates input, but always return the current state. State changes are
 * managed through the StateChange event of the _in member.
 * @return the current value held by this MemorySwitch;
 */
int InOut::Digital::MemorySwitch::do_read_value(void)
{
  _in->read_value();
  return _memory_state;
}

// Changes state only when high
void InOut::Digital::MemorySwitch::on_input_state_changed(const InOut::InOutBase* sender, int args)
{
  _memory_state ^= args;
}