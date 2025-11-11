#pragma once

namespace Util
{
  namespace Memory
  {
    /**
     * Basic behavior for smart pointers.
     * CAUTION: should not be used directly, but instanced via
     * concrete types instead.
     */
    template<typename T>
    class Smart_ptr
    {
      public:
        virtual ~Smart_ptr(void) 
        { 
          /* 
           * Empty body, make sure memory deallocation 
           * is implemented in concrete types
           */ 
        }

        T* get(void) const { return _data; }

        bool operator ==(const T* other) const { return _data == other; }
        bool operator ==(const Smart_ptr<T>& other) const { return _data == other._data; }
        bool operator !=(const T* other) const { return _data != other; }
        bool operator !=(const Smart_ptr<T>& other) const { return _data != other._data; }
        T* operator ->(void) const { return _data; }
        T& operator *(void) const { return *_data; }
        operator bool(void) const { return _data != nullptr; }

      protected:
        /**
         * Initializes this Smart_ptr as nullptr.
         * CAUTION: do not call explicitly.
         */
        Smart_ptr(void) = default;
        /**
         * Initializes this Smart_ptr with the provided pointer to
         * wrapped data.
         * @param data can be nullptr as well.
         */
        Smart_ptr(T* data) : _data{ data } { /*Empty body*/ }

        /**
         * @return wrapped data. Can be nullptr.
         */
        T* data(void) const { return _data; }

        /**
         * Replaces data with provided one.
         * CAUTION: does not manage memory !
         */
        void set_data(T* new_data)
        {
          _data = new_data;
        }

      private:
        T* _data;
    };
  }
}