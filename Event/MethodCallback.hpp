#pragma once

#include "Callback.hpp"

namespace Util
{
  namespace Event
  {
    class CallbackFactory;

    /**
     * Concrete implementation of Callback used for
     * instance methods. Holds reference to the 
     * class instance and method to call.
     */
    template<typename TC, typename TS, typename TA>
    class MethodCallback : public Callback<TS, TA>
    {
      public:
        virtual ~MethodCallback(void) = default;
        
        /**
         * @see Callback::call.
         */
        void call(TS* sender, TA args) override
        {
          (_instance->*_method)(sender, args);
        }

        /**
         * @see Callback::type
         */
        char type(void) const override
        {
          return 'M';
        }

        /**
         * @see Callback::equals
         * @param other to compare.
         * @return true if same type and equal instance pointer and equal
         *         pointer to method, false otherwise.
         */
        bool equals(const Callback<TS, TA>& other) const override
        {
          if (!Callback<TS, TA>::equals(other))
          {
            return false;
          }
          auto mc_other = (const MethodCallback<TC, TS, TA>&) other;
          return _instance == mc_other._instance && _method == mc_other._method;
        }

        friend class CallbackFactory;

      private:
        TC* _instance{ };
        void (TC::*_method)(TS*, TA);

        MethodCallback(TC* instance, void (TC::*method)(TS*, TA)) 
          : _instance{ instance }, _method{ method }
        {
          // Empty body
        }
    };
  }
}