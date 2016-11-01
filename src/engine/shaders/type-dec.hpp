#include <string>
#include <unordered_map>

namespace Engine
{
  namespace Shader
  {
    class TypeDec
    {
      public:
        typedef std::unordered_map <std::string, std::string> FieldsList;

      public:
        TypeDec(std::string name);

      public:
        TypeDec*
        addField(std::string type, std::string);

        FieldsList&
        getFields();

      private:
        std::string name_;
        FieldsList  fieldDec_;
    };
  } // namespace Shader
} // namespace Engine