#pragma once

#include "Callback.hpp"

namespace Util
{
  namespace Event
  {
    class CallbackFactory;
    
    /**
     * Concrete Callback implementation for non-instance
     * functions. Holds only the pointer to said function.
     */
    template<typename TS, typename TA>
    class FunctionCallback : public Callback<TS, TA>
    {
    public:
      virtual ~FunctionCallback(void) = default;

      /**
       * @see Callback::call.
       */
      void call(TS* sender, TA args) override
      {
        _function(sender, args);
      }

      /**
       * @see Callback::type
       */
      char type(void) const override
      {
        return 'F';
      }
      
      /**
       * @see Callback::equals
       * @param other to compare.
       * @return true if same type and same function pointed to,
       *         false otherwise.
       */
      bool equals(const Callback<TS, TA>& other) const override
      {
        if (!Callback<TS, TA>::equals(other))
        {
          return false;
        }

        return _function == ((const FunctionCallback<TS, TA>&) other)._function;
  
      }

      friend class CallbackFactory;
      friend class Eventhandler;

    private:
      void (*_function)(TS*, TA);
      
      FunctionCallback(void (*function)(TS*, TA)) : _function{ function } 
      {
        // Empty body
      }
    };
  }
}