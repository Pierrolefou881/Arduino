#pragma once

#include "Smart_ptr.hpp"

namespace Util
{
  namespace Memory
  {
    /**
     * Simple implementation of std::shared_ptr like smart pointer.
     */
    template<typename T>
    class S_ptr : public Smart_ptr<T>
    {
    public:
      /** 
       * Initializes this S_ptr as a nullptr 
       */
      S_ptr(void) = default;
      /**
       * Initializes this S_Ptr with the provided pointer. Reference count starts then
       * at 1, provided data is not nullptr.
       * @param data can be nullptr.
       */

      S_ptr(T* data) : Smart_ptr<T>{ data }
      { 
        if (data != nullptr)
        {
          *_reference_count += 1;
        } 
      }

      S_ptr(const S_ptr<T>& other) : Smart_ptr<T>{ other.data() }, _reference_count{ other._reference_count }
      {
        if (other != nullptr)
        {
          *_reference_count += 1;
        }
      }

      S_ptr(S_ptr<T>&& other) noexcept : Smart_ptr<T>{ other.data() }, _reference_count{ other._reference_count }
      {
        if (other)
        {
          *_reference_count += 1;
        }
      }

      virtual ~S_ptr(void)
      {
        decrease_reference_count();
      }

      S_ptr<T>& operator =(T* data)
      {
        assign(data, new unsigned int{ 0 });
        return *this;
      }

      S_ptr<T>& operator =(const S_ptr<T>& other)
      {
        assign(other.get(), other._reference_count);
        return *this; 
      }

      S_ptr<T>& operator =(S_ptr<T>&& other)
      {
        assign(other.get(), other._reference_count);
        return *this;
      }

      #ifdef _TEST
      unsigned int get_reference_count(void) const
      {
        return *_reference_count;
      }
      #endif

    private:
      unsigned int* _reference_count{ new unsigned int{ 0 } };

      void decrease_reference_count(void)
      {
        *_reference_count -= 1;
        if ((*_reference_count) == 0)
        {
          delete _reference_count;
          delete this->data();
        }
      }

      void assign(T* data, unsigned int* reference_count)
      {
        // don't treat if data is identical
        if (this->data() == data)
        {
          return;
        }

        // update reference count
        if (this->data() != nullptr)
        {
          decrease_reference_count();
        }
        _reference_count = reference_count;
        
        if (data != nullptr)  // Do not reference nullptr
        {
          *_reference_count += 1;
        }

        this->set_data(data);
      }
    };
  }
}