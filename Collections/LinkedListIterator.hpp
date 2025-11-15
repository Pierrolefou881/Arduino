#pragma once

#include "BaseIterator.hpp"
#include "LinkedList.hpp"

namespace Util
{
  namespace Collection
  {
    /**
     * Concrete implementation of BaseIterator to be used with
     * LinkedList. Greatly improves performance when iterating over
     * all the collection.
     */
    template<typename T>
    class LinkedListIterator : public BaseIterator<T>
    {
    public:
      LinkedListIterator(Util::Collection::LinkedList<T>* list) : _list{ list } { }
      /**
       * @return true if there is another element down the
       * iterated collection.
       */
      bool has_next(void) const override
      {
        return _list->_next != nullptr;
      }

      /**
       * Moves to the next element in the list, if possible.
       */
      virtual void next(void) override
      {
        if (has_next())
        {
          _list = _list->_next.get();
        }
      }

      /**
       * @return the current element of the iterated collection.
       */
      virtual T& get(void) const
      {
        return  _list->_next->_data;
      }

    private:
      Util::Collection::LinkedList<T>* _list{ };
    };
  }
}