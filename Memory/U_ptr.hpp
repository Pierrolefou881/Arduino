#pragma once

#include "Smart_ptr.hpp"

namespace Util
{
  namespace Memory
  {
    /**
     * Simple implementation of std::unique_ptr like smart
     * pointer. Because T is unknown, U_ptr cannot copy data,
     * it should be done by other classes like factories.
     */
    template<typename T>
    class U_ptr : public Smart_ptr<T>
    {
    public:
      /**
       * Initializes this U_ptr as a nullptr.
       */
      U_ptr(void) = default;

      /**
       * Initializes this U_ptr with the provided pointer to data.
       * @param data can be nullptr.
       */
      U_ptr(T* data) : Smart_ptr<T>{ data } { /*Empty body*/ }

      /* Copy and move -> change data ownership */
      U_ptr(const U_ptr<T>& other) 
      {
        change_ownership(other);
      }

      U_ptr(U_ptr<T>&& other) noexcept 
      {
        change_ownership(other);
      }

      virtual ~U_ptr(void) { delete this->data(); }

      U_ptr<T>& operator =(T* data) 
      { 
        if (this->data() != nullptr)
        {
          delete this->data();
        }

        this->set_data(data);
        return *this; 
      }

      U_ptr<T>& operator =(const U_ptr<T>& other)
      {
        if (this->data() != nullptr)
        {
          delete this->data();
        }

        change_ownership(other);
        return *this;
      }

      U_ptr<T>& operator =(U_ptr<T>&& other) noexcept
      {
        if (this->data() != nullptr)
        {
          delete this->data();
        }
        
        change_ownership(other);
        return *this;
      }

    private:
      void change_ownership(const U_ptr<T>& other)
      {
        this->set_data(other.data());
        other.set_data(nullptr);
      }
      void change_ownership(U_ptr<T>&& other)
      {
        this->set_data(other.data());
        other.set_data(nullptr);
      }
    };
  }
}