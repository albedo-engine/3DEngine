#include "shader-generator.hpp"

namespace Engine
{
  namespace Shader
  {

    ShaderGenerator::ShaderGenerator(std::string name)
                    : name_(name)
    { }

    ShaderGenerator::~ShaderGenerator()
    { }

    std::vector<std::string>
    ShaderGenerator::generateShader()
    {
      auto output = generateFragmentShaderGraph();
      if (output == nullptr)
        throw std::logic_error("ShaderGenerator: at least one output "
                               "should be given");

      // Creates all user defined types
      // at the beginning of the file
      fragmentStack_.push_back("// STRUCTS DECLARATION\n");
      for (auto tIt = typeDecMap_.begin(); tIt != typeDecMap_.end(); ++tIt)
      {
        fragmentStack_.push_back("struct " + tIt->first + "\n");
        fragmentStack_.push_back("{\n");

        auto& fields = tIt->second->getFields();
        for (auto fIt = fields.begin(); fIt != fields.end(); fIt++)
        {
          auto fieldStr = fIt->second + " " + fIt->first;
          fragmentStack_.push_back("\t" + fieldStr + ";\n");
        }

        fragmentStack_.push_back("};\n");
      }
      fragmentStack_.push_back("// END STRUCTS DECLARATION\n\n");

      // Creates all required uniforms
      // at the beginning of the file
      fragmentStack_.push_back("// UNIFORMS DECLARATION\n");
      for (auto uIt = uniformMap_.begin(); uIt != uniformMap_.end(); ++uIt)
      {
        auto& u = uIt->second;
        auto uniformStr = "uniform " + u->getType() + " " + u->getName();

        fragmentStack_.push_back(uniformStr);

        if (!u->getDefaultValue().empty())
          fragmentStack_.push_back(" = " + u->getDefaultValue() + ";");
        fragmentStack_.push_back("\n");
      }
      fragmentStack_.push_back("// END UNIFORMS DECLARATION\n\n");

      // Adds all include to the top of the file
      fragmentStack_.push_back("// INCLUDES\n");
      for (auto& text : includeStack_)
        fragmentStack_.push_back(text);
      fragmentStack_.push_back("\n// END INCLUDES\n\n");

      // Begins the main function
      // containing the shader logic
      fragmentStack_.push_back("void main()\n{\n");

      // Creates all required variable at
      // the beginning of the main function
      fragmentStack_.push_back("\t// VARIABLE DECLARATION\n");
      for (auto vIt = variablesMap_.begin(); vIt != variablesMap_.end(); ++vIt)
      {
        auto& var = vIt->second;
        fragmentStack_.push_back("\t");
        if (!var->getPrefix().empty())
          fragmentStack_.push_back(var->getPrefix() + " ");
        fragmentStack_.push_back(var->getType() + " " + var->getName() + ";\n");
      }
      fragmentStack_.push_back("\t// END VARIABLE DECLARATION\n\n");

      traverse(output);

      fragmentStack_.push_back("\n}");

      clean();

      return fragmentStack_;
    }

    ShaderNode*
    ShaderGenerator::generateFragmentShaderGraph()
    {
      // Declares the light structure
      declareStruct("Material")
        ->addField("color", "vec3");

      declareStruct("Light")
        ->addField("position", "vec3")
        ->addField("material", "Material");

      auto alphavar = this->createVariable("vec4", "alpha", "const");
      auto light = this->createStructVariable("Light", "light");
      auto light2 = this->createStructVariable("Light", "lightBlue", "const");

      auto inlineCode1 = this->createNode<InlineNode>()
                          ->text("${output0} = vec4(0, 0, 0, 0);")
                          ->output(alphavar);

      auto inlineCode = this->createNode<InlineNode>()
                        ->text("${output0} = ${input0};")
                        ->input(light2->field("material")->field("color"))
                        ->output(light->field("material")->field("color"));

      return inlineCode;
    }

    VariableNode*
    ShaderGenerator::createVariable(std::string type,
                                    std::string name,
                                    std::string prefix)
    {
      auto elt = variablesMap_.find(name);
      if (elt != variablesMap_.end())
        return elt->second;

      auto typeDecElt = typeDecMap_.find(type);
      if (typeDecElt != typeDecMap_.end())
      {
        throw std::logic_error("ShaderGenerator: use the createStructVariable "
                               "method for user defined types");
      }

      auto var = createNode<VariableNode>();
      var->setType(type);
      var->setName(name);
      var->setPrefix(prefix);

      variablesMap_[name] = var;

      return var;
    }

    StructVariableNode*
    ShaderGenerator::createStructVariable(std::string type,
                                          std::string name,
                                          std::string prefix)
    {

      auto var = createStructVariableRec(type, name);
      var->setPrefix(prefix);

      variablesMap_[name] = var;
      return var;
    }

    StructVariableNode*
    ShaderGenerator::createStructVariableRec(std::string type, std::string name)
    {
      auto typeDecElt = typeDecMap_.find(type);
      if (typeDecElt == typeDecMap_.end())
      {
        throw std::logic_error("ShaderGenerator: use the createVariable "
                                 "method for predefined types");
      }

      std::unordered_map<std::string, VariableNode*> vars;

      auto& structFields = typeDecElt->second->getFields();
      for (auto fIt = structFields.begin(); fIt != structFields.end(); ++fIt)
      {
        auto varName = name + "." + fIt->first;

        VariableNode* varField = nullptr;
        if (typeDecMap_.find(fIt->second) == typeDecMap_.end())
        {
          varField = createNode<VariableNode>();
          varField->setType(fIt->second);
          varField->setName(varName);
        }
        else
          varField = createStructVariableRec(fIt->second, varName);

        vars[fIt->first] = varField;
      }

      auto var = createNode<StructVariableNode>();
      var->init(vars);

      var->setName(name);
      var->setType(type);

      return var;
    }

    TypeDec*
    ShaderGenerator::declareStruct(std::string name)
    {
      auto elt = typeDecMap_.find(name);
      if (elt != typeDecMap_.end())
        throw std::logic_error("ShaderGenerator: you cannot declare twice "
                                 " the same structure");

      TypeDec* type = new TypeDec(name);
      typeDecMap_[name] = type;

      return type;
    }

    UniformNode*
    ShaderGenerator::requestUniform(std::string type,
                                    std::string name,
                                    std::string defaultValue)
    {
      auto elt = uniformMap_.find(name);
      if (elt != uniformMap_.end())
        return elt->second;

      auto uniformNode = createNode<UniformNode>();
      uniformNode->setType(type);
      uniformNode->setName(name);
      uniformNode->setDefaultValue(defaultValue);

      uniformMap_[name] = uniformNode;

      return uniformNode;
    }

    void
    ShaderGenerator::include(std::string text)
    {
      includeStack_.push_back(text);
    }

    void
    ShaderGenerator::traverse(ShaderNode* node)
    {
      if (nodes_[node])
        return;
      nodes_[node] = true;

      for (auto input : node->getInputs())
        traverse(input);

      if (dynamic_cast<VariableNode*>(node) == nullptr)
        fragmentStack_.push_back("\t" + node->toString() + "\n");
    }

    void
    ShaderGenerator::clean()
    {
      // Cleans every allocated nodes
      for (auto& nodeVist : nodes_)
      {
        auto& nodePtr = nodeVist.first;
        if (nodePtr != nullptr)
          delete nodePtr;
      }

      // Cleans type declarations
      for (auto& tElt : typeDecMap_)
        delete tElt.second;

    }
  } // namespace Shader
} // namespace Engine