#pragma once

namespace Util
{
  namespace Event
  {
    /**
     * Defines basic behaviour for callbacks:
     * call, type information and comparison.
     */
    template<typename TS, typename TA>
    class Callback
    {
    public:
      virtual ~Callback(void) = default;

      /**
       * Calls the referenced method with the provided
       * arguments.
       * @param sender that invoked the event.
       * @param args parameters that define the reason for the event.
       */
      virtual void call(TS* sender, TA args) = 0;

      /**
       * Identifies concrete types with a character.
       * @return the character that identifies concrete implementations
       *         of Callback base class.
       */
      virtual char type(void) const = 0;

      bool operator ==(const Callback& other) const
      {
        return equals(other);
      }

      bool operator !=(const Callback& other) const
      {
        return !equals(other);
      }

      /**
       * @param other to compare.
       * @return true if both this and other share the same type.
       */
      virtual bool equals(const Callback& other) const
      {
        return type() == other.type();
      }
    };
  }
}