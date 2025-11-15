#pragma once
#include "BaseList.hpp"
#include <S_ptr.hpp>

namespace Util
{
  namespace Collection
  {
    template<typename U>
    class LinkedListIterator;

    /**
     * Dynamic LinkedList that can be used when
     * accessing specific indices is not performance
     * crucial.
     */
    template<typename T>
    class LinkedList : public BaseList<T>
    {
    public:
      /**
       * Initilaizes this LinkedList as an empty list.
       */
      LinkedList(void) = default;
      virtual ~LinkedList(void) = default;

      /**
       * Adds the specified element at the given index. if
       * no index is specified, pushes the object at the
       * beginning of this LinkedList.
       * @param data to add.
       * @param index of insertion. Default value is 0.
       * @return true if insertion successful, false otherwise.
       */
      bool add(const T& data, unsigned int index = 0) override
      {
        auto insertion_link = index > 0 ? find_link(index) : this;
        if (insertion_link == nullptr)  // Out of bounds
        {
          return false;
        }

        // Insert data here
        auto tmp = insertion_link->_next;
        insertion_link->_next = new LinkedList(data);
        insertion_link->_next->_next = tmp;
        return true;
      }

      /**
       * Adds the given object at the end of this LinkedList.
       * @param data to append.
       */
      void append(const T& data) override
      {
        if (_next == nullptr)
        {
          _next = new LinkedList<T>{ data };
        }
        else 
        {
          _next->append(data);
        }
      }

      /**
       * Removes element at given index, if it
       * exists. Does nothing otherwise. If not index
       * is provided, tries to remove the first item.
       * @param index of the removal.
       */
      void remove_at(unsigned int index = 0) override
      {
        auto deletion_link = find_link(index);
        if (deletion_link == nullptr)
        {
          return;
        }
        auto tmp = deletion_link->_next->_next;
        deletion_link->_next = tmp;
      }

      /**
       * Removes the first occurrence of the provided
       * element from this LinkedList. Does nothing if
       * not present.
       * @param data to remove.
       */
      void remove(const T& data) override
      {
        if (_next == nullptr) // List does not contain data
        {
          return;
        }
        if (_next->_data == data) // data found, remove.
        {
          auto tmp = _next->_next;
          _next = tmp;
          return;
        }
        
        // else try next link
        _next->remove(data);
      }

      /**
       * Removes all occurrences of the provided element
       * from this BaseList. Does nothing if none is present.
       * @param data to remove.
       */
      void remove_all(const T& data) override
      {
        if (_next == nullptr) // No more instance of data to find
        {
          return;
        }

        if (_next->_data == data) // Instance found, remove and rearrange
        {
          auto tmp = _next->_next;
          _next = tmp;
          remove_all(data);   // Redo a pass to delete consecutive data
        }
        else// Go to next link
        {
          _next->remove_all(data);
        }
      }

      /**
       * Removes all elements from this LinkedList.
       */
      void clear() override
      {
        _next = nullptr;
      }

      /**
       * Gets the element at the specified index.
       * If no index is specified, pops the first element,
       * if possible.
       * CAUTION: Ensure index is within bounds, arduino doesn't provide an
       *          exception system.
       * @param index of the object to look for.
       * @return element at index.
       */
      T& at(unsigned int index = 0) override
      {
        auto link = find_link(index);
        return link->_next->_data;
      }

      /**
       * @param data to look for.
       * @return true if at least one occurrence of data exists in this LinkedList,
       *         false otherwise.
       */
      bool contains(const T& data) const override
      {
        // Search recursively
        return _next != nullptr && (_next->_data == data || _next->contains(data));
      }

      /**
       * @return the size of this LinkedList.
       */
      unsigned int size(void) const override
      {
        // Call recursively, add 1 for each non null link
        return _next != nullptr ? 1 + _next->size() : 0;
      }

      friend class LinkedListIterator<T>;

    private:
      Util::Memory::S_ptr<LinkedList<T>> _next{ };
      T _data{ };

      // Private Ctor for link creation
      LinkedList(const T& data) : _data{ data } { }

      LinkedList<T>* find_link(unsigned int desired_index, unsigned int current_index = 0)
      {
        if (_next != nullptr)
        {
          if (desired_index == current_index) // Found
          {
            return this;
          }

          // Keep Searching
          return _next->find_link(desired_index, ++current_index);
        }
        return nullptr;   // Out of bounds
      }
    };
  }
}