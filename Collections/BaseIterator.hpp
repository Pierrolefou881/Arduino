#pragma once

namespace Util
{
  namespace Collection
  {
    /**
     * Defines behavior for iterator over Util::Collection
     * collections.
     */
    template <typename T>
    class BaseIterator
    {
    public:
      /**
       * @return true if there is another element down the
       * iterated collection.
       */
      virtual bool has_next(void) const = 0;

      /**
       * Moves to the next element in the list, if possible.
       */
      virtual void next(void) = 0;

      /**
       * @return the current element of the iterated collection.
       */
      virtual T& get(void) const = 0;

      virtual ~BaseIterator(void) = default;
    };
  }
}