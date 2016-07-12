#pragma once

#include <memory>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/variant.hpp>


namespace Engine
{
  namespace Data
  {
    class Store
    {
      public:
        typedef std::shared_ptr<Store> StorePtr;
        typedef std::unordered_map<std::string, boost::any> AttributesMap;

      public:
        static inline
        StorePtr
        create()
        {
          return std::make_shared<Store>();
        }

      public:
        template<typename T>
        const T& get_attribute(std::string attribute_name)
        {
          return boost::get<T>(attributes_[attribute_name]);
        }

        template<typename T>
        void set_attribute(std::string attribute_name, T value)
        {
          attributes_[attribute_name] = value;
        }

      private:
        AttributesMap attributes_;
    };
  } // namespace Data
} // namespace Engine

