#pragma once
#include "Callback.hpp"
#include "CallbackFactory.hpp"
#include <LinkedList.hpp>
#include <LinkedListIterator.hpp>
#include <U_ptr.hpp>
#include <S_ptr.hpp>

namespace Util
{
  namespace Event
  {
    template <typename TS, typename TA>
    class EventHandler
    {
    public:
      /**
       * Initializes this Eventhandler with an empty list of callbacks.
       */
      EventHandler(void) 
        : _callbacks{ new Util::Collection::LinkedList<Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>>{ } }
      {
        // Empty body
      }

      virtual ~EventHandler(void) = default;

      /**
       * Registers a function callback to be called when this EventHandler
       * is triggered.
       */
      void add(void (*func)(TS*, TA))
      {
        auto callback = Util::Event::CallbackFactory::create_callback(func);
        add(callback);
      }

      /**
       * Registers an instance method for a given class instance and method
       * to be called when this EventHandler is triggered.
       * CAUTION: manage instance lifespan carefully.
       * @param instance of which method shall be called.
       * @param method of the instance to be called.
       */
      template<typename TC>
      void add(TC* instance, void (TC::*method)(TS*, TA))
      {
        auto callback = Util::Event::CallbackFactory::create_callback(instance, method);
        add(callback);
      }

      /**
       * Registers the provided callback, if not already present.
       * @param callback to register
       */
      void add(const Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>& callback)
      {
        if (!contains(callback))
        {
          _callbacks->append(callback);
        }
      }

      /**
       * Removes the provided function from this EventHandler.
       * Does nothing if not present.
       * @param fun to remove.
       */
      void remove(void (*func)(TS*, TA))
      {
        auto callback = Util::Event::CallbackFactory::create_callback(func);
        remove(callback);
      }

      /**
       * Removes the method for the given instance from this EventHandler.
       * Does nothing if not found.
       * @param instance of which method is called.
       * @param method of the instance to be called.
       */
      template<typename TC>
      void remove(TC* instance, void (TC::*method)(TS*, TA))
      {
        auto callback = Util::Event::CallbackFactory::create_callback(instance, method);
        remove(callback);
      }

      /**
       * Removes the provided callback from this EventHandler, if present.
       * Does nothing otherwise.
       * @param callback to be removed.
       */
      void remove(const Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>& callback)
      {
        Util::Collection::LinkedListIterator<Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>> iterator{ _callbacks.get() };
        unsigned int index = 0;
        while (iterator.has_next())
        {
          if (*(iterator.get()) == *callback)
          {
            _callbacks->remove_at(index);
            return;
          }
          index++;
          iterator.next();
        }
      }

      /**
       * Calls all callbacks contained in this EventHandler.
       * @param sender instigator of the call.
       * @param args defining the context of the call.
       */
      void call(TS* sender, TA args)
      {
        Util::Collection::LinkedListIterator<Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>> iterator{ _callbacks.get() };
        while (iterator.has_next())
        {
          iterator.get()->call(sender, args);
          iterator.next();
        }
      }

      /**
       * Removes all callbacks from this EventHandler.
       */
      void clear(void) const
      {
        _callbacks->clear();
      }

    private:
      Util::Memory::U_ptr<Util::Collection::LinkedList<Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>>> _callbacks{ };

      bool contains(const Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>& callback)
      {
        Util::Collection::LinkedListIterator<Util::Memory::S_ptr<Util::Event::Callback<TS, TA>>> iterator{ _callbacks.get() };
        while (iterator.has_next())
        {
          if(*(iterator.get()) == *callback)
          {
            return true;
          }
          iterator.next();
        }
        return false;
      }
    };
  }
}