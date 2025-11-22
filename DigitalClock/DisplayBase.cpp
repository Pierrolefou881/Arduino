#include "DisplayBase.hpp"
#include <LiquidCrystal.h>

/**
 * Initializes this DisplayBase with the provided liquid crystal screen reference.
 * @param screen to assign to this LiquiCrystal.
 */
DigitalClock::Display::DisplayBase::DisplayBase(const Util::Memory::S_ptr<LiquidCrystal>& screen)
 : _screen{ screen }
{
  // Empty body
}

/**
 * Called if regular update is needed. Does nothing by default, override
 * to implement specific behavior.
 */
void DigitalClock::Display::DisplayBase::update(void)
{
  // Empty body
}

/**
 * @return reference to the _screen member, non const for eventual modifications.
 */
Util::Memory::S_ptr<LiquidCrystal>& DigitalClock::Display::DisplayBase::get_screen(void)
{
  return _screen;
}