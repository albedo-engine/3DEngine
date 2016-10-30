#include "type-dec.hpp"

namespace Engine
{
  namespace Shader
  {
    TypeDec::TypeDec(std::string name)
            : name_(name)
    { }

    TypeDec*
    TypeDec::addField(std::string name, std::string type)
    {
      fieldDec_[name] = type;
      return this;
    }

    TypeDec::FieldsList&
    TypeDec::getFields()
    {
      return fieldDec_;
    }

  } // namespace Shader
} // namespace Engine