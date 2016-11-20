#pragma once

#include <memory>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/variant.hpp>


namespace Engine
{
  namespace Data
  {
    /** \class Store
     *
     * \brief Container class storing different types elements into an unique
     * unordered map.
     * The class is used as bridge between the application and the shaders.
     * It allows to map data to uniforms.
     */
    class Store
    {
      public:
        typedef std::shared_ptr<Store> StorePtr;
        typedef std::unordered_map<std::string, boost::any*> AttributesMap;

      public:
        static inline
        StorePtr
        create()
        {
          return std::make_shared<Store>();
        }

      public:
        ~Store();

      public:
        template<typename T>
        const T*
        get(std::string attribute_name) const
        {
          auto found = attributes_.find(attribute_name);
          if (found == attributes_.end())
            return nullptr;

          return boost::any_cast<T>(attributes_.at(attribute_name));
        }

        /** \brief Adds/Modifies an attribute in the store.
         *
         * \param attribute_name
         * the key (represented by a string) of the attribute to add/modify.
         * \param value
         * The value to add at the given key.
         */
        template<typename T>
        void
        set(std::string attribute_name, T value)
        {
          auto attribute = get_ptr(attribute_name);
          if (attribute != nullptr)
          {
            delete attribute;
            attributes_.erase(attribute_name);
          }

          attributes_[attribute_name] = new boost::any(value);
        }

        template<typename T>
        void
        remove(std::string attribute_name)
        {
          auto attribute = get_ptr(attribute_name);
          if (attribute == nullptr)
            return;

          delete attribute;
          attributes_.erase(attribute_name);
        }

      public:
        const AttributesMap&
        getAttributesMap();

      private:
        boost::any*
        get_ptr(std::string attribute_name)
        {
          auto pair = attributes_.find(attribute_name);
          if (pair == attributes_.end() || (*pair).second == nullptr)
            return nullptr;

          return attributes_[attribute_name];
        }

      private:
        AttributesMap attributes_;
    };
  } // namespace Data
} // namespace Engine

