#pragma once
#include "BaseList.hpp"

namespace Util
{
  namespace Collection
  {
    /**
     * Simple array list for primitive types, pointers
     * or smart pointers. T must have a default value
     * to avoid errors.
     */
    template <typename T>
    class ArrayList : public BaseList<T>
    {
    public:
      /**
       * Adds the specified element at the given index. if
       * no index is specified, pushes the object at the
       * beginning of this ArrayList.
       * @param data to add.
       * @param index of insertion. Default value is 0.
       * @return true if insertion successful, false otherwise.
       */
      bool add(const T& data, unsigned int index = 0) override
      {
        // Fail if out of bounds.
        if (index >= _current_size)
        {
          return false;
        }

        check_size(_current_size + 1);
        _current_size++;

        // Offset the rest of the list to the right.
        auto insertion_value = data;
        for (auto current_index = index; current_index < _current_size; current_index++)
        {
          auto tmp = _data[current_index];
          _data[current_index] = insertion_value;
          insertion_value = tmp;
        }

        return true;
      }

      /**
       * Adds the given object at the end of this
       * ArrayList.
       * @param data to append.
       */
      void append(const T& data) override
      {
        check_size(_current_size + 1);
        _data[_current_size] = data;
        _current_size++;
      }

      /**
       * Removes element at given index, if it
       * exists. Does nothing otherwise. If not index
       * is provided, tries to remove the first item.
       * @param index of the removal.
       */
      void remove_at(unsigned int index = 0) override
      {
        // if out of bounds, do nothing.
        if (index >= _current_size)
        {
          return;
        }
        
        _current_size--;
        // remove and rearrange
        for (auto current_index = index; current_index < _current_size; current_index++)
        {
          _data[current_index] = _data[current_index + 1]; 
        }
        
        check_size(_current_size);
      }

      /**
       * Removes the first occurrence of the provided
       * element from this ArrayList. Does nothing if
       * not present.
       * @param data to remove.
       */
      void remove(const T& data) override
      {
        // Search for object
        unsigned int current_index;
        for (current_index = 0; 
            current_index < _current_size && _data[current_index] != data; 
            current_index++)
          ;  // Empty body.

        // If object not found, do nothing
        if (current_index == _current_size)
        {
          return;
        }

        // object found, remove and rearrange

        _current_size--;
        check_size(_current_size);
      }

      /**
       * Removes all occurrences of the provided element
       * from this ArrayList. Does nothing if none is present.
       * @param data to remove.
       */
      void remove_all(const T& data) override
      {
        // Check all values
        for(int current_index = _current_size - 1; current_index >= 0; current_index--)
        {
          if (_data[current_index] == data)
          {
            // Move to the far end and decrease size, put data out of bounds.
            for (unsigned int remove_index = current_index; remove_index < _current_size - 1; remove_index++)
            {
              auto tmp = _data[remove_index + 1];
              _data[remove_index + 1] = _data[remove_index];
              _data[remove_index] = tmp;
            }

            _current_size--;
          }
        }

        check_size(_current_size);
      }

      /**
       * Removes all elements from this ArrayList.
       */
      void clear() override
      {
        _current_size = 0;
        check_size(_current_size);
      }

      /**
       * Gets the element at the specified index.
       * If no index is specified, pops the first element,
       * if possible. If no item found, gets a default value.
       * CAUTION: Ensure index is within bounds, Arduino does not provide
       *          stdexcept for such cases.
       * @param index of the object to look for.
       * @return element at index, or default value.
       */
      T& at(unsigned int index = 0) override
      {
        return _data[index];
      }

      /**
       * @param data to look for.
       * @return true if at least one occurrence of data exists in this ArrayList,
       *         false otherwise.
       */
      bool contains(const T& data) const override
      {
        unsigned int current_index;
        for (current_index = 0; 
            current_index < _current_size && _data[current_index] != data; 
            current_index++)
        ; // Empty body
        return current_index != _current_size;
      }

      /**
       * @return the size of this ArrayList.
       */
      unsigned int size(void) const override
      {
        return _current_size;
      }

      // TEST method, not relevant when deployed.
      #ifdef _TEST
      unsigned int array_length(void) const
      {
        return _array_capacity;
      }
      #endif

    private:
      static const unsigned int _DEFAULT_SIZE = 3;
      static const unsigned int _RESIZE_FACTOR = 2;

      T* _data{ new T[_DEFAULT_SIZE] };
      unsigned int _array_capacity{ _DEFAULT_SIZE };
      unsigned int _current_size{ 0 };

      void check_size(unsigned int future_size)
      {
        if (future_size > _array_capacity)
        {
          auto expanded_capacity = _array_capacity * _RESIZE_FACTOR;
          resize(expanded_capacity);
        }
        else if (_array_capacity / future_size >= _RESIZE_FACTOR)
        {
          auto shrunk_capacity = _array_capacity / _RESIZE_FACTOR;
          resize(shrunk_capacity);
        }
      }

      void resize(unsigned int new_size)
      {
        auto resized = new T[new_size];
        for (unsigned int i = 0; i < _current_size; i++)
        {
          resized[i] = _data[i];
        }

        delete _data;
        _data = resized;
        _array_capacity = new_size;
      }
    };
  }
}