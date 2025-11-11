#pragma once

#include "FunctionCallback.hpp"
#include "MethodCallback.hpp"
#include <S_ptr.hpp>

namespace Util
{
  namespace Event
  {
    class CallbackFactory
    {
    public:

      /**
       * Creates a new instance of Callback using the provided
       * pointer to function.
       * @param func must not be null.
       * @return a callback wrapping the func pointer.
       */
      template<typename TS, typename TA>
      static Util::Memory::S_ptr<Callback<TS, TA>> create_callback(void (*func)(TS*, TA))
      {
        return { new FunctionCallback<TS, TA>{ func } };
      }

      /**
       * Creates a new instance of Callback using the provided
       * class instance and instance method. CAUTION: beware of instance lifespan.
       * @param instance must not be null.
       * @param method to call.
       */
      template<typename TC, typename TS, typename TA>
      static Util::Memory::S_ptr<Callback<TS, TA>> create_callback(TC* instance, void (TC::*method)(TS*, TA))
      {
        return { new MethodCallback<TC, TS, TA>{ instance, method } };
      }
    };
  }
}