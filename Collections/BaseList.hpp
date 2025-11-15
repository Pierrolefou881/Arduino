#pragma once

#include "BaseIterator.hpp"

namespace Util
{
  namespace Collection
  {
    /**
     * Defines basic behavior for all list type collections.
     */
    template<typename T>
    class BaseList
    {
    public:
      /**
       * Adds the specified element at the given index. if
       * no index is specified, pushes the object at the
       * beginning of this BaseList.
       * @param data to add.
       * @param index of insertion. Default value is 0.
       * @return true if insertion successful, false otherwise.
       */
      virtual bool add(const T& data, unsigned int index = 0) = 0;

      /**
       * Adds the given object at the end of this BaseList.
       * @param data to append.
       */
      virtual void append(const T& data) = 0;

      /**
       * Removes element at given index, if it
       * exists. Does nothing otherwise. If not index
       * is provided, tries to remove the first item.
       * @param index of the removal.
       */
      virtual void remove_at(unsigned int index = 0) = 0;

      /**
       * Removes the first occurrence of the provided
       * element from this BaseList. Does nothing if
       * not present.
       * @param data to remove.
       */
      virtual void remove(const T& data) = 0;

      /**
       * Removes all occurrences of the provided element
       * from this BaseList. Does nothing if none is present.
       * @param data to remove.
       */
      virtual void remove_all(const T& data) = 0;

      /**
       * Removes all elements from this BaseList.
       */
      virtual void clear() = 0;

      /**
       * Gets the element at the specified index.
       * If no index is specified, pops the first element,
       * if possible.
       * @param index of the object to look for.
       * @return element at index.
       */
      virtual T& at(unsigned int index = 0) = 0;

      /**
       * @param data to look for.
       * @return true if at least one occurrence of data exists in this BaseList,
       *         false otherwise.
       */
      virtual bool contains(const T& data) const = 0;

      /**
       * @return the size of this BaseList.
       */
      virtual unsigned int size(void) const = 0;

      virtual ~BaseList(void) = default;

      T& operator [](unsigned int index)
      {
        return at(index);
      }
    };
  }
}