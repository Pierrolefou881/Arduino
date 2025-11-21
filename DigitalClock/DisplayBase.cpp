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

Util::Memory::S_ptr<LiquidCrystal>& DigitalClock::Display::DisplayBase::get_screen(void)
{
  return _screen;
}